#include "game.h"
#include <notification.h>
#include <cliDisplay.h>
#include <spell.h>
#include <enchantment.h>
#include <haste.h>
#include <banish.h>
#include <unsummon.h>
#include <disenchant.h>
#include <blizzard.h>
#include <recharge.h>
#include <raiseDead.h>
#include <enchantmentDecorator.h>
#include <activatedMinion.h>
#include <novicePyromancer.h>
#include <cloner.h>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Game::Game(const string& deck1, const string& deck2, const string& initFilePath, bool isTesting, bool bonusFeatures)
    : isPlayer1Turn{true}, isTesting{isTesting}, bonusFeatures{bonusFeatures}, player1Wins {std::nullopt}, display{}, player1{}, player2{} {

    // initialize triggerTopics
    triggerTopics.insert(std::make_pair(TriggerType::EndTurnPlayer1, make_unique<TriggerTopic>(*this)));
    triggerTopics.insert(std::make_pair(TriggerType::EndTurnPlayer2, make_unique<TriggerTopic>(*this)));
    triggerTopics.insert(std::make_pair(TriggerType::StartTurnPlayer1, make_unique<TriggerTopic>(*this)));
    triggerTopics.insert(std::make_pair(TriggerType::StartTurnPlayer2, make_unique<TriggerTopic>(*this)));
    triggerTopics.insert(std::make_pair(TriggerType::MinionEnter, make_unique<TriggerTopic>(*this)));
    triggerTopics.insert(std::make_pair(TriggerType::MinionLeave, make_unique<TriggerTopic>(*this)));

    ifstream initFile(initFilePath);
    if (!initFile) {
        throw runtime_error("Failed to open game initialization file: " + initFilePath);
    }
    string player1Name, player2Name;
    getline(initFile, player1Name);
    getline(initFile, player2Name);

    player1 = make_unique<Player>(player1Name, this);
    player2 = make_unique<Player>(player2Name, this);

    player1->setOtherPlayer(player2.get());
    player2->setOtherPlayer(player1.get());

    player1->initializeDeck(deck1, !isTesting);
    player2->initializeDeck(deck2, !isTesting);

    // default to CliDisplay. can add more display options in the future
    display = make_unique<CliDisplay>(*player1, *player2);

    player1->declareStart();
}

void Game::notifyTopic(TriggerType tt, const Notification& notification) const {
    triggerTopics.at(tt)->notifyTriggers(notification);
}

void Game::attachTrigger(TriggerType tt, Trigger* trigger)const  {
    triggerTopics.at(tt)->attachTrigger(trigger);
}

TriggerTopic* Game::getTriggerTopic(TriggerType tt) const { return triggerTopics.at(tt).get(); }

void Game::endTurn(std::stringstream& ss) {
    if (isPlayer1Turn) {
        player1->declareEnd();
        isPlayer1Turn = false;
        player2->declareStart();
    }
    else {
        player2->declareEnd();
        isPlayer1Turn = true;
        player1->declareStart();
    }
}
void Game::discardCard(std::stringstream& ss) {
    if (!isTesting) {
        cout << "discard is only available in testing mode." << endl;
        return;
    }
    // i is 1-indexed. in fact, everything through the cli is 1-indexed for simplicity
    int i;
    ss >> i;
    --i;
    isPlayer1Turn ? player1->discardCard(i) : player2->discardCard(i);
}
void Game::drawCard(std::stringstream& ss) {
    if (!isTesting) {
        cout << "draw is only available in testing mode." << endl;
        return;
    }
    isPlayer1Turn ? player1->drawCard() : player2->drawCard();
}
void Game::attack(std::stringstream& ss) {
    size_t i,j;
    ss >> i;
    i--; // it is 0-indexed!
    Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
    Player& otherPlayer = *currPlayer.getOtherPlayer();
    if (ss >> j) {
        j--; // it is 0-indexed!
        //  orders the active player’s minion i to attack the inactive player’s minion j
        if (i >= currPlayer.getBoard().size()) {
            throw out_of_range("Specified attacking minion index, while attacking minion, out of range.");
        }
        if (j >= otherPlayer.getBoard().size()) {
            throw out_of_range("Specified target minion index out of range.");
        }
        Minion* minion = dynamic_cast<Minion*> (currPlayer.getBoard()[i].get());
        Minion* target = dynamic_cast<Minion*> (otherPlayer.getBoard()[j].get());
        if (minion && target) {
            if (!minion->attackMinion(target, std::nullopt, true)) {
                cout << "Attacking minion does not have enough action points." << endl;
            }
        }
        else {
            if (!minion) {
                cout << "Attacking unit is not a minion." << endl;
            }
            if (!target) {
                cout << "Target is not a minion." << endl;
            }            
        }
    } else {
        // orders minion i to attack the opposing player, where 1 is the leftmost minion and 5 is the rightmost minion
        if (i >= currPlayer.getBoard().size()) {
            throw out_of_range("Specified attacking minion index, while attacking player, out of range");
        }
        if (Minion* minion = dynamic_cast<Minion*> (currPlayer.getBoard()[i].get())) {
            bool success = minion->attackPlayer(std::nullopt);
            if (!success) {
                cout << "Insufficient action points on the minion." << endl;
                return;
            }
        }
        else {
            cout << "The indicated card is not a minion. " << endl;
        }
    }
}
void Game::playCard(std::stringstream& ss) {
    // play i p t: plays the ith card in the active player’s hand on card t owned by player p
    Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
    size_t i,p;
    ss >> i;
    if (i<1 || i>currPlayer.getHand().size()) {
        cout << "play: invalid i" << endl;
        return;
    }
    i--; // it's 0-indexed!
    const std::unique_ptr<Card>& playingCard = currPlayer.getHand()[i];
    const int cost = playingCard->get_cost();
    if (!isTesting && currPlayer.getMagic() < cost) {
        cout << "Not enough magic to play this card." << endl;
        return;
    }
    if (ss>>p) {
        Player& targetPlayer = p == 1 ? *player1 : *player2;
        if (p!=1 && p!=2) {
            cout << "play i p t: invalid p. p must be 1 or 2" << endl;
            return;
        }
        string t;
        ss >> t;
        if (t=="r") {
            // use ritual
            auto target = targetPlayer.getRitual();
            if (!target) {
                cout << "No ritual found when using play i p t" << endl;
            }
            if (auto spell = dynamic_cast<Banish*> (playingCard.get())) {
                if (spell->action(target)) {
                    currPlayer.discardCard(i);
                }
            } else if (auto spell = dynamic_cast<Recharge*>(playingCard.get())) {
                if (&targetPlayer!=&currPlayer) {
                    cout << "can't call recharge on the other player" << endl;
                    return;
                }
                if (spell->action(target)) currPlayer.discardCard(i);
            }
            else {
                cout << "Invalid card played on ritual target." << endl;
            }
            
        } else {
            size_t targetCardIndex;
            try {
                targetCardIndex = stoi(t);
            } catch (const exception& e) {
                cout << "play i p t: invalid t" << endl;
                return;
            }
            
            if (targetCardIndex<1 || targetCardIndex>targetPlayer.getBoard().size()) {
                cout << "play i p t: invalid t" << endl;
                return;
            }
            targetCardIndex--;
            // get target minion
            auto& targetCard = targetPlayer.getBoard()[targetCardIndex];
            if (!dynamic_cast<Minion*> (targetCard.get())) {
                throw runtime_error("Target unit not a minion in play i p t");
            }
            auto targetMinion = dynamic_cast<Minion*> (targetCard.get());
            if (dynamic_cast<Enchantment*> (playingCard.get())) {
                auto ownedEnchantment = dynamic_cast<EnchantmentDecorator*> (currPlayer.stealCard(i, Hand).release());
                if (!ownedEnchantment) {
                    throw runtime_error("Cannot find correct enchantment while in play i p t and target is a minion.");
                }
                if (dynamic_cast<Haste*> (ownedEnchantment)) {
                    // we need to increase an action for haste
                    targetMinion->setActions(targetMinion->getActions() + 1);
                }
                targetMinion->addEnchantment(std::unique_ptr<EnchantmentDecorator> (ownedEnchantment));
            }
            else if (dynamic_cast<Unsummon*> (playingCard.get()) || dynamic_cast<Disenchant*> (playingCard.get()) || dynamic_cast<Banish*> (playingCard.get())) {
                auto spell = dynamic_cast<Spell*> (playingCard.get());
                if (spell->action(targetMinion)) {
                    currPlayer.discardCard(i);
                }
            }
            else {
                cout << "Invalid playing card type while in play i p t and target is a minion." << endl;
            }
        }
    } else {
        
        // play i plays the ith card in the active player’s hand with no target
        if (dynamic_cast<Minion*> (playingCard.get())) {
            // check if there are already 5 minions on the board
            if (currPlayer.getBoard().size() >= 5) {
                cout << "There are already 5 minions on the board, cannot put another one" << endl;
                return;
            }
            currPlayer.moveCard(i, Hand, Board);
        }
        else if (dynamic_cast<RaiseDead*> (playingCard.get()) || dynamic_cast<Blizzard*> (playingCard.get())) {
            auto spell = dynamic_cast<Spell*> (playingCard.get());
            if (spell->action(static_cast<Minion*> (nullptr))) {
                currPlayer.discardCard(i);
            }
        }
        else if (dynamic_cast<Recharge*> (playingCard.get())) {
            auto spell = dynamic_cast<Spell*> (playingCard.get());
            if (spell->action(static_cast<Ritual*> (nullptr))) {
                currPlayer.discardCard(i);
            }
        }
        else if (dynamic_cast<Ritual*> (playingCard.get())) {
            auto ownedRitual = std::unique_ptr<Ritual> (dynamic_cast<Ritual*> (currPlayer.stealCard(i, Hand).release()));
            currPlayer.setRitual(std::move(ownedRitual));
        }
        else {
            cout << "The unit picked should need a target." << endl;
        }
    }
    if (isTesting) {
        currPlayer.setMagic(max(0, currPlayer.getMagic() - cost));
    }
    else {
        currPlayer.setMagic(currPlayer.getMagic() - cost);
    }
}
void Game::useCard(std::stringstream& ss) {
    // use i p t: command orders that minion to use its activated ability on the provided target (or on no target)
    Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
    size_t i,p;
    ss >> i;
    
    if (i<1 || i>currPlayer.getBoard().size()) throw invalid_argument("play: invalid i");
    i--; // it's 0-indexed!
    const std::unique_ptr<Card>& playingCard = currPlayer.getBoard()[i];
    if (ss>>p) {
        Player& targetPlayer = p == 1 ? *player1 : *player2;
        if (p!=1 && p!=2) {
            cout << "use i p t: invalid p. p must be 1 or 2" << endl;
            return;
        }
        string t;
        ss >> t;
        int targetCardIndex;
        try {
            targetCardIndex = stoi(t);
        } catch (const exception& e) {
            cout << "use i p t: invalid t" << endl;
            return;
        }
        if (targetCardIndex<1 || targetCardIndex>5) throw invalid_argument("use i p t: invalid t");
        targetCardIndex--;
        auto& targetCard = targetPlayer.getBoard()[targetCardIndex];
        if (!dynamic_cast<Minion*> (targetCard.get())) {
            throw runtime_error("Target unit not a minion in play i p t");
        }
        auto targetMinion = dynamic_cast<Minion*> (targetCard.get());
        if (dynamic_cast<NovicePyromancer*>(playingCard.get()) || dynamic_cast<Cloner*>(playingCard.get())) {
            auto novicePyromancer = dynamic_cast<NovicePyromancer*>(playingCard.get());
            auto cloner = dynamic_cast<Cloner*> (playingCard.get());
            UseSkillStatus status = OK;
            if (novicePyromancer) {
                status = novicePyromancer->useSkill(isTesting, targetMinion);
            } 
            else {
                status = cloner->useSkill(isTesting, targetMinion);
            }
            switch(status) {
                case NotEnoughMagic: 
                    cout << "Not enough magic. " << endl;
                    return;
                case NoAction:
                    cout << "Not enough action points." << endl;
                    return;
                case Silenced: 
                    cout << "Silence in effect, cannot use ability." << endl;
                    return;
                default:
                    cout << "Used activated ability successfully." << endl;
            }
        } else if (dynamic_cast<ActivatedMinion*>(playingCard.get())) {
            cout << "The minion's activated ability does not have a target" << endl;
        } else {
            cout << "The minion has no activated abilities" << endl;
        }
    } else {
        // minion uses its activated ability on no target
        if (dynamic_cast<NovicePyromancer*>(playingCard.get()) || dynamic_cast<Cloner*>(playingCard.get())) {
            cout << "The minion's activated abilility requires a target" << endl;
        } else if (dynamic_cast<ActivatedMinion*>(playingCard.get())) {
            auto playingMinion = dynamic_cast<ActivatedMinion*>(playingCard.get());
            auto status = playingMinion->useSkill(isTesting);
            switch(status) {
                case NotEnoughMagic:
                    cout << "Not enough magic." << endl;
                    return;
                case NoAction:
                    cout << "Not enough action points." << endl;
                    return;
                case Silenced: 
                    cout << "Silence in effect, cannot use ability." << endl;
                    return;
                default:
                    cout << "Used activated ability successfully." << endl;
            }
        } else {
            cout << "The minion has no activated abilities" << endl;
        }
    }
}
void Game::inspectMinion(std::stringstream& ss) {
    // inspect i command inspects the ith minion owned by the active player
    int minion;
    ss >> minion;
    display->inspectMinion(isPlayer1Turn, minion);
}
void Game::displayHand(std::stringstream& ss) {
    display->showHand(isPlayer1Turn);
}
void Game::displayBoard(std::stringstream& ss) {
    display->showBoard();
}

void Game::declareWin(bool isPlayer1) const {
    if (player1Wins) {
        // there's already a winner
        return;
    }
    player1Wins = isPlayer1;
}

const Player& Game::getCurrentPlayer() const {
    return isPlayer1Turn ? *player1 : *player2;
}

std::optional<bool> Game::isPlayer1Wins() const {
    return player1Wins;
}
