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
    : isPlayer1Turn{false}, isTesting{isTesting}, triggerTopics{}, display{}, player1{}, player2{}, player1Wins {std::nullopt} {
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

    player1->initializeDeck(deck1);
    player2->initializeDeck(deck2);

    // default to CliDisplay. can add more display options in the future
    display = make_unique<CliDisplay>(*player1, *player2);

    string command;
    while (getline(initFile, command)) {
        trimWhitespace(command);
        executeCommand(command);
    }
}

void Game::notifyTopic(TriggerType triggerType, Notification notification) const {
    triggerTopics.at(triggerType)->notifyTriggers(notification);
}

void Game::attachTrigger(TriggerType tt, Trigger* trigger)const  {
    triggerTopics.at(tt)->attachTrigger(trigger);
}


TriggerTopic* Game::getTriggerTopic(TriggerType triggerType) const { return triggerTopics.at(triggerType).get(); }
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
    ss.exceptions(ios::failbit | ios::badbit);

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
        if (!isTesting) throw invalid_argument("discard is only available in testing mode.");
        int i;
        ss >> i;
        isPlayer1Turn ? player1->discardCard(i) : player2->discardCard(i);
    } else if (primary_cmd=="draw") {
        if (!isTesting) throw invalid_argument("draw is only availabld in testing mode.");
        isPlayer1Turn ? player1->drawCard() : player2->drawCard();
    } else if (primary_cmd=="attack") {
        int i,j;
        ss >> i;
        Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
        Player& otherPlayer = *currPlayer.getOtherPlayer();
        if (ss >> j) {
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
                bool success = minion->attackMinion(target, std::nullopt);
                if (!success) {
                    throw runtime_error("Attacking minion does not have enough action points.");
                }
            }
            else {
                if (!minion) {
                    throw runtime_error("Attacking unit is not a minion.");
                }
                if (!target) {
                    throw runtime_error("Target is not a minion.");
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
                    throw runtime_error("Insufficient action points on the minion.");
                    return;
                }
            }
            else {
                throw runtime_error("The indicated card is not a minion. ");
            }
        }
    } else if (primary_cmd=="play") {
        // play i p t: plays the ith card in the active player’s hand on card t owned by player p
        Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
        int i,p;
        ss >> i;
        if (i<1 || i>currPlayer.getHand().size()) throw invalid_argument("play: invalid i");
        const std::unique_ptr<Card>& playingCard = currPlayer.getHand()[i];
        if (ss>>p) {
            Player& targetPlayer = p == 1 ? *player1 : *player2;
            if (p!=1 && p!=2) throw invalid_argument("play i p t: invalid p. p must be 1 or 2");
            string t;
            ss >> t;
            if (t=="r") {
                // use ritual
                auto target = targetPlayer.getRitual();
                if (!target) {
                    throw runtime_error("no ritual found when using play i p t");
                }
                if (auto spell = dynamic_cast<Banish*> (playingCard.get())) {
                    auto ownedCard = currPlayer.stealCard(i, Hand);
                    auto ownedSpell = std::unique_ptr<Spell> (dynamic_cast<Spell*> (ownedCard.get())); 
                    ownedSpell->action(target);
                }
                else {
                    throw runtime_error ("Invalid card played on ritual target.");
                }
                
            } else {
                int targetCardIndex;
                try {
                    targetCardIndex = stoi(t);
                } catch (const exception& e) {
                    throw invalid_argument("play i p t: invalid t");
                }
                if (targetCardIndex<1 || targetCardIndex>targetPlayer.getBoard().size()) throw invalid_argument("play i p t: invalid t");
                // get target minion
                auto& targetCard = targetPlayer.getBoard()[targetCardIndex];
                if (!dynamic_cast<Minion*> (targetCard.get())) {
                    throw runtime_error("target unit not a minion in play i p t");
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
                    auto ownedSpell = dynamic_cast<Spell*> (currPlayer.stealCard(i, Hand).release());
                    if (!ownedSpell) {
                        throw runtime_error ("Cannot find correct spell while in play i p t and target is a minion.");
                    }
                    ownedSpell->action(targetMinion);
                }
                else {
                    throw runtime_error ("Invalid playing card type while in play i p t and target is a minion.");
                }
            }
        } else {
            // play i plays the ith card in the active player’s hand with no target
            if (dynamic_cast<Minion*> (playingCard.get())) {
                // check if there are already 5 minions on the board
                if (currPlayer.getBoard().size() >= 5) {
                    throw runtime_error("There are already 5 minions on the board, cannot put another one");
                }
                currPlayer.moveCard(i, Hand, Board);
            }
            else if (dynamic_cast<RaiseDead*> (playingCard.get()) || dynamic_cast<Recharge*> (playingCard.get()) || dynamic_cast<Blizzard*> (playingCard.get())) {
                auto ownedSpell = std::unique_ptr<Spell> (dynamic_cast<Spell*> (currPlayer.stealCard(i, Hand).release()));
                if (!ownedSpell) {
                    throw runtime_error("The unit picked is not a spell.");
                }
                ownedSpell->action(static_cast<Minion*> (nullptr));
            }
            else if (dynamic_cast<Ritual*> (playingCard.get())) {
                auto ownedRitual = std::unique_ptr<Ritual> (dynamic_cast<Ritual*> (currPlayer.stealCard(i, Hand).release()));
                if (!ownedRitual) {
                    throw runtime_error("The unit picked is not a ritual.");
                }
                currPlayer.setRitual(std::move(ownedRitual));
            }
            else {
                throw runtime_error("The unit picked should need a target.");
            }
        }
    } else if (primary_cmd=="use") {
        // use i p t: command orders that minion to use its activated ability on the provided target (or on no target)
        const Player& currPlayer = isPlayer1Turn ? *player1 : *player2;
        int i,p;
        ss >> i;
        if (i<1 || i>currPlayer.getHand().size()) throw invalid_argument("play: invalid i");
        const std::unique_ptr<Card>& playingCard = currPlayer.getHand()[i];
        if (ss>>p) {
            if (p!=1 && p!=2) throw invalid_argument("play i p t: invalid p. p must be 1 or 2");
            string t;
            ss >> t;
            if (t=="r") {
                // use ritual
                
            } else {
                int target_card;
                try {
                    target_card = stoi(t);
                } catch (const exception& e) {
                    throw invalid_argument("play i p t: invalid t");
                }
                if (target_card<1 || target_card>5) throw invalid_argument("play i p t: invalid t");
                // TODO
            }
        } else {
            // play i plays the ith card in the active player’s hand with no target
            // TODO
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
        throw invalid_argument("invalid command: " + cmd);
    }
}

void Game::declareWin(bool isPlayer1) const {
    if (player1Wins) {
        // there's already a winner
        return;
    }
    player1Wins = isPlayer1;
}

