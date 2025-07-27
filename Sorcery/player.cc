#include "player.h"
#include "util.h"
#include "game.h"
#include "minions/airElemental.h"
#include "minions/earthElemental.h"
#include "minions/fireElemental.h"
#include "minions/potionSeller.h"
#include "minions/novicePyromancer.h"
#include "minions/apprenticeSummoner.h"
#include "minions/masterSummoner.h"
#include "spells/banish.h"
#include "spells/unsummon.h"
#include "spells/recharge.h"
#include "spells/disenchant.h"
#include "spells/raiseDead.h"
#include "spells/blizzard.h"
#include "enchantments/giantStrength.h"
#include "enchantments/magicFatigue.h"
#include "enchantments/silence.h"
#include "rituals/darkRitual.h"
#include "rituals/auraOfPower.h"
#include "rituals/standstill.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

Player::Player(string& name, Game* game): name{std::move(name)}, life{STARTING_LIFE}, magic{STARTING_MAGIC}, deck{}, hand{}, board{}, graveyard{}, ritual{}, otherPlayer{nullptr}, game{game} {}

// draw command draws a card, similar to the effect if the player just started their turn
void Player::drawCard() {
    if (deck.empty() || deck.size()>=5) return;
    unique_ptr<Card> card = std::move(deck.back());
    deck.pop_back();
    hand.push_back(std::move(card));
}
void Player::playCard(Card* card) {}

// discard the i'th card in the player's hand
// the card does not go to the graveyard, trigger leave play effects or anything else
void Player::discardCard(int i) {
    if (i<0 || i>= hand.size()) {
        throw runtime_error("invalid hand index to discard card");
    }
    hand.erase(hand.begin() + i);
}

void Player::notifyGame(TriggerType triggerType) {
    game->notifyTopic(triggerType);
}
bool Player::moveCard(Minion* minion, Area src, Area dst) { return false; }
bool Player::modifyLife(int life) { return false; }
const vector<unique_ptr<Card>>& Player::getHand() const { return hand; }
const vector<unique_ptr<Card>>& Player::getDeck() const { return deck; }
const vector<unique_ptr<Card>>& Player::getBoard() const { return board; }
void Player::setOtherPlayer(Player* player) {
    otherPlayer = player;
}
void Player::initializeDeck(const string& deckFilePath) {
    ifstream initFile(deckFilePath);
    if (!initFile) {
        throw runtime_error("Failed to open deck initialization file: " + deckFilePath);
    }

    string card_string;
    while (getline(initFile, card_string)) {
        if (card_string == AIR_ELEMENTAL) {
            deck.push_back(make_unique<AirElemental>());
        } else if (card_string == EARTH_ELEMENTAL) {
            deck.push_back(make_unique<EarthElemental>());
        } else if (card_string == FIRE_ELEMENTAL) {
            deck.push_back(make_unique<FireElemental>());
        } else if (card_string == POTION_SELLER) {
            deck.push_back(make_unique<PotionSeller>());
        } else if (card_string == NOVICE_PYROMANCER) {
            deck.push_back(make_unique<NovicePyromancer>());
        } else if (card_string == APPRENTICE_SUMMONER) {
            deck.push_back(make_unique<ApprenticeSummoner>());
        } else if (card_string == MASTER_SUMMONER) {
            deck.push_back(make_unique<MasterSummoner>());
        } else if (card_string == BANISH) {
            deck.push_back(make_unique<Banish>());
        } else if (card_string == UNSUMMON) {
            deck.push_back(make_unique<Unsummon>());
        } else if (card_string == RECHARGE) {
            deck.push_back(make_unique<Recharge>());
        } else if (card_string == DISENCHANT) {
            deck.push_back(make_unique<Disenchant>());
        } else if (card_string == RAISE_DEAD) {
            deck.push_back(make_unique<RaiseDead>());
        } else if (card_string == BLIZZARD) {
            deck.push_back(make_unique<Blizzard>());
        } else if (card_string == GIANT_STRENGTH) {
            deck.push_back(make_unique<GiantStrength>());
        } else if (card_string == MAGIC_FATIGUE) {
            deck.push_back(make_unique<MagicFatigue>());
        } else if (card_string == SILENCE) {
            deck.push_back(make_unique<Silence>());
        } else if (card_string == DARK_RITUAL) {
            deck.push_back(make_unique<DarkRitual>());
        } else if (card_string == AURA_OF_POWER) {
            deck.push_back(make_unique<AuraOfPower>());
        } else if (card_string == STANDSTILL) {
            deck.push_back(make_unique<Standstill>());
        }
    }

    shuffleDeck();

    // draw 5 cards from deck into hand
    for (int i=0;i<STARTING_NUM_CARDS;++i) {
        drawCard();
    }
}

void Player::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}