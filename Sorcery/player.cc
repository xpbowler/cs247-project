#include "player.h"

#include <iostream>
#include <fstream>

using namespace std;

const int STARTING_LIFE = 20;
const int STARTING_MAGIC = 3;
const int STARTING_NUM_CARDS = 5;

Player::Player(const string& deck, string& name): name{move(name)}, life{STARTING_LIFE}, magic{STARTING_MAGIC}, deck{}, hand{}, board{}, graveyard{}, ritual{}, otherPlayer{nullptr} {
    initializeDeck(deck);

}
// draw command draws a card, similar to the effect if the player just started their turn
void Player::drawCard() {}
void Player::playCard(Card* card) {}

// discard the i'th card in the player's hand
// the card does not go to the graveyard, trigger leave play effects or anything else
void Player::discardCard(int i) {}
void Player::notifyGame(TriggerType triggerType) {}
bool Player::moveCard(Minion* minion, Area src, Area dst) {}
bool Player::modifyLife(int life) {}
const vector<unique_ptr<Card>>& Player::getHand() {}
const vector<unique_ptr<Card>>& Player::getDeck() {}
const vector<unique_ptr<Card>>& Player::getBoard() {}
void Player::addTrigger(Trigger* trigger) {}
void Player::removeTrigger(Trigger* trigger) {}
void Player::initializeDeck(const string& deckFilePath) {
    ifstream initFile(deckFilePath);
    if (!initFile) {
        throw runtime_error("Failed to open deck initialization file: " + deckFilePath);
    }
    string card;
    while (getline(initFile, card)) {
        
    }
}