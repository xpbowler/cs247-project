#include "game.h"

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

Game::Game(const string& deck1, const string& deck2, const string& initFilePath, bool isTesting): isPlayer1Turn{false}, isTesting{isTesting}, triggerTopics{}, display{}, player1{}, player2{} {
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
    display = make_unique<CliDisplay>();

    string command;
    while (getline(initFile, command)) {
        trimWhitespace(command);
        executeCommand(command);
    }
}

void Game::notifyTopic(TriggerType triggerType) {
    // TODO 
}

void Game::attachTrigger(TriggerType tt, Trigger* trigger) {
    triggerTopics[tt]->attachTrigger(trigger);
}


TriggerTopic* Game::getTriggerTopic(TriggerType triggerType) const { return triggerTopics.at(triggerType).get(); }
void Game::play() {
    string command;
    while (getline(cin, command)) {
        trimWhitespace(command);
        if (command=="quit") break;
        executeCommand(command);
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
        isPlayer1Turn = !isPlayer1Turn;
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
        if (ss >> j) {
            //  orders the active player’s minion i to attack the inactive player’s minion j
            // TODO
        } else {
            // orders minion i to attack the opposing player, where 1 is the leftmost minion and 5 is the rightmost minion
            // TODO
        }
    } else if (primary_cmd=="play" || primary_cmd=="use") {
        // play i p t: plays the ith card in the active player’s hand on card t owned by player p
        // use i p t: command orders that minion to use its activated ability on the provided target (or on no target)

        int i,p;
        ss >> i;
        if (i<1 || i>5) throw invalid_argument("play: invalid i");

        if (ss>>p) {
            if (p!=1 && p!=2) throw invalid_argument("play i p t: invalid p. p must be 0 or 1");
            string t;
            ss >> t;
            if (t=="r") {
                // TODO
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
        // TODO
        display->inspectMinion(isPlayer1Turn, minion);
    } else if (primary_cmd=="hand") {
        display->showHand(isPlayer1Turn);
    } else if (primary_cmd=="board") {
        display->showBoard();
    } else {
        throw invalid_argument("invalid command: " + cmd);
    }
}