#include "player.h"
#include "airElemental.h"
#include "earthElemental.h"
#include "fireElemental.h"
#include "potionSeller.h"
#include "novicePyromancer.h"
#include "apprenticeSummoner.h"
#include "masterSummoner.h"
#include "banish.h"
#include "unsummon.h"
#include "recharge.h"
#include "disenchant.h"
#include "raiseDead.h"
#include "blizzard.h"
#include "giantStrength.h"
#include "magicFatigue.h"
#include "silence.h"
#include "darkRitual.h"
#include "auraOfPower.h"
#include "standstill.h"
#include <iostream>
#include <fstream>

using namespace std;

const int STARTING_LIFE = 20;
const int STARTING_MAGIC = 3;
const int STARTING_NUM_CARDS = 5;

Player::Player(string& name): name{move(name)}, life{STARTING_LIFE}, magic{STARTING_MAGIC}, deck{}, hand{}, board{}, graveyard{}, ritual{}, otherPlayer{nullptr} {}
// draw command draws a card, similar to the effect if the player just started their turn
void Player::drawCard() {}
void Player::playCard(Card* card) {}

// discard the i'th card in the player's hand
// the card does not go to the graveyard, trigger leave play effects or anything else
void Player::discardCard(int i) {}
void Player::notifyGame(TriggerType triggerType) {}
bool Player::moveCard(Minion* minion, Area src, Area dst) { return false; }
bool Player::modifyLife(int life) { return false; }
const vector<unique_ptr<Card>>& Player::getHand() { return hand; }
const vector<unique_ptr<Card>>& Player::getDeck() { return deck; }
const vector<unique_ptr<Card>>& Player::getBoard() { return board; }
void Player::addTrigger(Trigger* trigger) {}
void Player::removeTrigger(Trigger* trigger) {}
void Player::setOtherPlayer(Player* player) {
    otherPlayer = player;
}
void Player::initializeDeck(const string& deckFilePath) {
    ifstream initFile(deckFilePath);
    if (!initFile) {
        throw runtime_error("Failed to open deck initialization file: " + deckFilePath);
    }
    string card_string;
    this->deck = vector<unique_ptr<Card>>();
    while (getline(initFile, card_string)) {
        if (card_string == "Air Elemental") {
            deck.push_back(make_unique<Card>(make_unique<AirElemental>()));
        } else if (card_string == "Earth Elemental") {
            deck.push_back(make_unique<Card>(make_unique<EarthElemental>()));
        } else if (card_string == "Fire Elemental") {
            deck.push_back(make_unique<Card>(make_unique<FireElemental>()));
        } else if (card_string == "Potion Seller") {
            deck.push_back(make_unique<Card>(make_unique<PotionSeller>()));
        } else if (card_string == "Novice Pyromancer") {
            deck.push_back(make_unique<Card>(make_unique<NovicePyromancer>()));
        } else if (card_string == "Apprentice Summoner") {
            deck.push_back(make_unique<Card>(make_unique<ApprenticeSummoner>()));
        } else if (card_string == "Master Summoner") {
            deck.push_back(make_unique<Card>(make_unique<MasterSummoner>()));
        } else if (card_string == "Banish") {
            deck.push_back(make_unique<Card>(make_unique<Banish>()));
        } else if (card_string == "Unsummon") {
            deck.push_back(make_unique<Card>(make_unique<Unsummon>()));
        } else if (card_string == "Recharge") {
            deck.push_back(make_unique<Card>(make_unique<Recharge>()));
        } else if (card_string == "Disenchant") {
            deck.push_back(make_unique<Card>(make_unique<Disenchant>()));
        } else if (card_string == "Raise Dead") {
            deck.push_back(make_unique<Card>(make_unique<RaiseDead>()));
        } else if (card_string == "Blizzard") {
            deck.push_back(make_unique<Card>(make_unique<Blizzard>()));
        } else if (card_string == "Giant Strength") {
            deck.push_back(make_unique<Card>(make_unique<GiantStrength>()));
        } else if (card_string == "Magic Fatigue") {
            deck.push_back(make_unique<Card>(make_unique<MagicFatigue>()));
        } else if (card_string == "Silence") {
            deck.push_back(make_unique<Card>(make_unique<Silence>()));
        } else if (card_string == "Dark Ritual") {
            deck.push_back(make_unique<Card>(make_unique<DarkRitual>()));
        } else if (card_string == "Aura of Power") {
            deck.push_back(make_unique<Card>(make_unique<AuraOfPower>()));
        } else if (card_string == "Standstill") {
            deck.push_back(make_unique<Card>(make_unique<Standstill>()));
        }
    }
}