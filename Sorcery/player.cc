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
#include "minions/boneGolem.h"
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
#include <memory>

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
bool Player::modifyLife(int life) { 
    this->life += life;
    return true;
}
const vector<unique_ptr<Card>>& Player::getHand() const { return hand; }
const vector<unique_ptr<Card>>& Player::getDeck() const { return deck; }
const vector<unique_ptr<Card>>& Player::getBoard() const { return board; }
void Player::addTrigger(Trigger* trigger) {}
void Player::removeTrigger(Trigger* trigger) {}
void Player::setOtherPlayer(Player* player) {
    otherPlayer = player;
}
// call after set other player
void Player::initializeDeck(const string& deckFilePath) {
    ifstream initFile(deckFilePath);
    if (!initFile) {
        throw runtime_error("Failed to open deck initialization file: " + deckFilePath);
    }

    string card_string;
    while (getline(initFile, card_string)) {
        if (card_string == "Air Elemental") {
            deck.push_back(std::unique_ptr<Card> (new AirElemental(*this, *otherPlayer)));        
        } else if (card_string == "Earth Elemental") {
            deck.push_back(std::unique_ptr<Card> (new EarthElemental(*this, *otherPlayer)));
        } else if (card_string == "Fire Elemental") {
            deck.push_back(std::unique_ptr<Card> (new FireElemental(*this, *otherPlayer)));
        } else if (card_string == "Potion Seller") {
            deck.push_back(std::unique_ptr<Card> (new PotionSeller(*this, *otherPlayer)));
        } else if (card_string == "Novice Pyromancer") {
            deck.push_back(std::unique_ptr<Card> (new NovicePyromancer(*this, *otherPlayer)));
        } else if (card_string == "Apprentice Summoner") {
            deck.push_back(std::unique_ptr<Card> (new ApprenticeSummoner(*this, *otherPlayer)));
        } else if (card_string == "Bone Golem") {
            deck.push_back(std::unique_ptr<Card> (new BoneGolem(*this, *otherPlayer)));
        } else if (card_string == "Master Summoner") {
            deck.push_back(std::unique_ptr<Card> (new MasterSummoner(*this, *otherPlayer)));
        } else if (card_string == "Banish") {
            deck.push_back(std::unique_ptr<Card> (new Banish(*this, *otherPlayer)));
        } else if (card_string == "Unsummon") {
            deck.push_back(std::unique_ptr<Card> (new Unsummon(*this, *otherPlayer)));
        } else if (card_string == "Recharge") {
            deck.push_back(std::unique_ptr<Card> (new Recharge(*this, *otherPlayer)));
        } else if (card_string == "Disenchant") {
            deck.push_back(std::unique_ptr<Card> (new Disenchant(*this, *otherPlayer)));
        } else if (card_string == "Raise Dead") {
            deck.push_back(std::unique_ptr<Card> (new RaiseDead(*this, *otherPlayer)));
        } else if (card_string == "Blizzard") {
            deck.push_back(std::unique_ptr<Card> (new Blizzard(*this, *otherPlayer)));
        } else if (card_string == "Giant Strength") {
            deck.push_back(std::unique_ptr<Card> (new GiantStrength(*this, *otherPlayer)));
        } else if (card_string == "Magic Fatigue") {
            deck.push_back(std::unique_ptr<Card> (new MagicFatigue(*this, *otherPlayer)));
        } else if (card_string == "Silence") {
            deck.push_back(std::unique_ptr<Card> (new Silence(*this, *otherPlayer)));
        } else if (card_string == "Dark Ritual") {
            deck.push_back(std::unique_ptr<Card> (new DarkRitual(*this, *otherPlayer)));
        } else if (card_string == "Aura of Power") {
            deck.push_back(std::unique_ptr<Card> (new AuraOfPower(*this, *otherPlayer)));
        } else if (card_string == "Standstill") {
            deck.push_back(std::unique_ptr<Card> (new Standstill(*this, *otherPlayer)));
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

void Player::summonMinion(MinionType minionType, int amount) {
    int summonAmount = min(5 - board.size(), (unsigned long) amount);
    for (int i = 0; i < summonAmount; i++) {
        switch (minionType) {
            case AE: 
                board.push_back(std::unique_ptr<Card> (new AirElemental(*this, *otherPlayer)));
            break;
            case EE:
                board.push_back(std::unique_ptr<Card> (new EarthElemental(*this, *otherPlayer)));
            break;
            case NP:
                board.push_back(std::unique_ptr<Card> (new NovicePyromancer(*this, *otherPlayer)));
            break;
            case MS: 
                board.push_back(std::unique_ptr<Card> (new MasterSummoner(*this, *otherPlayer)));
            break;
            case AS: 
                board.push_back(std::unique_ptr<Card> (new ApprenticeSummoner(*this, *otherPlayer)));
            break;
            case BG:
                board.push_back(std::unique_ptr<Card> (new BoneGolem (*this, *otherPlayer)));
            break;
            case FE:
                board.push_back(std::unique_ptr<Card> (new FireElemental(*this, *otherPlayer)));
            break;
            case PS:
                board.push_back(std::unique_ptr<Card> (new PotionSeller (*this, *otherPlayer)));
            break;
        }
    }
}