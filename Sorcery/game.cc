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

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Trim leading and trailing whitespace from command
void trimWhitespace(string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    if (start == string::npos) s = "";
    else s = s.substr(start, end - start + 1);
}

Game::Game(const string& deck1, const string& deck2, const string& initFilePath, bool isTesting)
    : isPlayer1Turn{true}, isTesting{isTesting}, triggerTopics{}, display{}, player1{}, player2{}, player1Wins {std::nullopt} {

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

    string command;
    while (getline(initFile, command)) {
        trimWhitespace(command);
        executeCommand(command);
    }
}

void Game::notifyTopic(TriggerType tt, const Notification& notification) const {
    triggerTopics.at(tt)->notifyTriggers(notification);
}

void Game::attachTrigger(TriggerType tt, Trigger* trigger)const  {
    triggerTopics.at(tt)->attachTrigger(trigger);
}


TriggerTopic* Game::getTriggerTopic(TriggerType tt) const { return triggerTopics.at(tt).get(); }
void Game::play() {
    string command;
    while (getline(cin, command)) {
        trimWhitespace(command);
        if (command=="quit") break;
        executeCommand(command);
        // check if winning here
        if (player1Wins) {
            if (*player1Wins) {
                cout << "Player 1 wins!" << endl;
            }
            else {
                cout << "Player 2 wins!" << endl;
            }
            break;
        }

    }
}
void Game::executeCommand(const string& cmd) {
    stringstream ss(cmd);
    ss.exceptions(ios::badbit);

    string primary_cmd;
    ss >> primary_cmd;
    
    if (primary_cmd=="help") {
        cout << "Commands:" << "\n"
             << "help -- Display this message." << "\n"
             << "end -- End the current player's turn." << "\n"
             << "quit -- End the game." << "\n"
             << "attack minion other-minion -- Orders minion to attack other-minion." << "\n"
             << "attack minion -- Orders minion to attack the opponent." << "\n"
             << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << "\n"
             << "use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << "\n"
             << "inspect minion -- View a minion's card and all enchantments on that minion." << "\n"
             << "hand -- Describe all cards in your hand." << "\n"
             << "board -- Describe all cards on the board." << endl;
    } else if (primary_cmd=="end") {
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
    } else if (primary_cmd=="discard") {
        if (!isTesting) {
            "discard is only available in testing mode.";
            return;
        }
        // i is 1-indexed. in fact, everything through the cli is 1-indexed for simplicity
        int i;
        ss >> i;
        --i;
        isPlayer1Turn ? player1->discardCard(i) : player2->discardCard(i);
    } else if (primary_cmd=="draw") {
        if (!isTesting) {
            "draw is only available in testing mode.";
            return;
        }
        isPlayer1Turn ? player1->drawCard() : player2->drawCard();
    } else if (primary_cmd=="attack") {
        int i,j;
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
    } else if (primary_cmd=="play") {
        // play i p t: plays the ith card in the active player’s hand on card t owned by player p
        Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
        int i,p;
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
                int targetCardIndex;
                try {
                    targetCardIndex = stoi(t);
                } catch (const exception& e) {
                    cout << "play i p t: invalid t" << endl;
                    return;
                }
                
                if (targetCardIndex<1 || targetCardIndex>targetPlayer.getBoard().size()) {
                    "play i p t: invalid t";
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
        
    } else if (primary_cmd=="use") {

        // use i p t: command orders that minion to use its activated ability on the provided target (or on no target)
        Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
        int i,p;
        ss >> i;
        
        if (i<1 || i>currPlayer.getBoard().size()) throw invalid_argument("play: invalid i");
        i--; // it's 0-indexed!
        const std::unique_ptr<Card>& playingCard = currPlayer.getBoard()[i];
        if (ss>>p) {
            Player& targetPlayer = p == 1 ? *player1 : *player2;
            if (p!=1 && p!=2) {
                "play i p t: invalid p. p must be 1 or 2";
                return;
            }
            string t;
            ss >> t;
            int targetCardIndex;
            try {
                targetCardIndex = stoi(t);
            } catch (const exception& e) {
                cout << "play i p t: invalid t" << endl;
                return;
            }
            if (targetCardIndex<1 || targetCardIndex>5) throw invalid_argument("play i p t: invalid t");
            targetCardIndex--;
            auto& targetCard = targetPlayer.getBoard()[targetCardIndex];
            if (!dynamic_cast<Minion*> (targetCard.get())) {
                throw runtime_error("Target unit not a minion in play i p t");
            }
            auto targetMinion = dynamic_cast<Minion*> (targetCard.get());
            if (dynamic_cast<NovicePyromancer*>(playingCard.get())) {
                auto playingMinion = dynamic_cast<NovicePyromancer*>(playingCard.get());
                auto status = playingMinion->useSkill(isTesting, targetMinion);
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
                }
            } else if (dynamic_cast<ActivatedMinion*>(playingCard.get())) {
                cout << "The minion's activated ability does not have a target" << endl;
            } else {
                cout << "The minion has no activated abilities" << endl;
            }
        } else {
            // minion uses its activated ability on no target
            if (dynamic_cast<NovicePyromancer*>(playingCard.get())) {
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
                }
            } else {
                cout << "The minion has no activated abilities" << endl;
            }
        }
    } else if (primary_cmd=="inspect") { // TODO. doc says describe. is it describe or inspect
        // inspect i command inspects the ith minion owned by the active player
        int minion;
        ss >> minion;
        display->inspectMinion(isPlayer1Turn, minion);
    } else if (primary_cmd=="hand") {
        display->showHand(isPlayer1Turn);
    } else if (primary_cmd=="board") {
        display->showBoard();
    } else {
        cout << "Invalid command: " << cmd << endl;
    }
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

