#include "controller.h"
#include "game.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>

using namespace std;

// Trim leading and trailing whitespace from command
void trimWhitespace(string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    if (start == string::npos) s = "";
    else s = s.substr(start, end - start + 1);
}

Controller::Controller(Game& game): game{game} {}

void Controller::play() {
    string command;
    while (getline(cin, command)) {
        trimWhitespace(command);
        if (command=="quit") break;
        executeCommand(command);
        // check if winning here
        std::optional<bool> player1Wins = game.isPlayer1Wins();
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

void Controller::initGame(const string& initFilePath) {
    ifstream initFile(initFilePath);
    if (!initFile) {
        throw runtime_error("Failed to open game initialization file: " + initFilePath);
    }
    string player1Name, player2Name;
    getline(initFile, player1Name);
    getline(initFile, player2Name);
    
    string command;
    while (getline(initFile, command)) {
        trimWhitespace(command);
        executeCommand(command);
    }
}

void Controller::executeCommand(const string& cmd) {
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
        game.endTurn(ss);
    } else if (primary_cmd=="discard") {
        game.discardCard(ss);
    } else if (primary_cmd=="draw") {
        game.drawCard(ss);
    } else if (primary_cmd=="attack") {
        game.attack(ss);
    } else if (primary_cmd=="play") {
        game.playCard(ss);
    } else if (primary_cmd=="use") {
        game.useCard(ss);
    } else if (primary_cmd=="inspect") {
        game.inspectMinion(ss);
    } else if (primary_cmd=="hand") {
        game.displayHand(ss);
    } else if (primary_cmd=="board") {
        game.displayBoard(ss);
    } else {
        cout << "Invalid command: " << cmd << endl;
    }
}
