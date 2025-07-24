#include "game.h"
#include <iostream>
#include <fstream>

using namespace std;

Game::Game(const std::string& deck1, const std::string& deck2, const std::string& initFilePath, bool isTesting): isPlayer1Turn{false}, triggerTopics{}, player1{}, player2{} {
    ifstream initFile(initFilePath);
    if (!initFile) {
        throw runtime_error("Failed to open initialization file: " + initFilePath);
    }
    string player1Name, player2Name;
    getline(initFile, player1Name);
    getline(initFile, player2Name);

    player1 = make_unique<Player>(deck1, player1Name);
    player2 = make_unique<Player>(deck2, player2Name);

    string command;
    while (getline(initFile, command)) {
        executeCommand(command);
    }
    
}

void Game::notifyTopic(TriggerType triggerType) {}
void Game::addTrigger(TriggerType triggerType, Trigger* trigger) {}
void Game::removeTrigger(TriggerType triggerType, Trigger* trigger) {}
void Game::play() {}
void Game::executeCommand(const string& command) {}