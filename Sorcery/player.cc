#include "player.h"
#include <helper.h>
#include <game.h>
#include <card.h>
#include <airElemental.h>
#include <earthElemental.h>
#include <fireElemental.h>
#include <potionSeller.h>
#include <novicePyromancer.h>
#include <apprenticeSummoner.h>
#include <masterSummoner.h>
#include <boneGolem.h>
#include <banish.h>
#include <unsummon.h>
#include <recharge.h>
#include <disenchant.h>
#include <raiseDead.h>
#include <blizzard.h>
#include <giantStrength.h>
#include <magicFatigue.h>
#include <silence.h>
#include <darkRitual.h>
#include <auraOfPower.h>
#include <standstill.h>
#include <baseEnchantment.h>
#include <notification.h>


#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <memory>
#include <variant>

using namespace std;

namespace {
    std::vector<std::unique_ptr<Card>>::iterator findCard (std::vector<std::unique_ptr<Card>>& vec, Card* card) {
        for (auto it = vec.begin(); it != vec.end(); it++) {
            if (it->get() == card) {
                return it;
            }
        }
        return vec.end();
    }
}

//=========================================================
Player::Player(string& name, Game* game): name{std::move(name)}, life{STARTING_LIFE}, magic{STARTING_MAGIC}, deck{}, hand{}, board{}, graveyard{}, ritual{}, otherPlayer{nullptr}, game{*game} {}

//=========================================================
// draw command draws a card, similar to the effect if the player just started their turn
void Player::drawCard() {
    if (deck.empty() || hand.size()>=5) return;
    unique_ptr<Card> card = std::move(deck.back());
    deck.pop_back();
    hand.push_back(std::move(card));
}

//=========================================================
void Player::playCard(int i) {
    // PRECOND: hand.size() > i
    // check if it is a ritual first
    auto& tempCard = hand[i];
    if (dynamic_cast<Ritual*> (tempCard.get())) {
        auto ownedRitual = dynamic_cast<Ritual*> (tempCard.release());
        ritual.reset(ownedRitual);
    }
    moveCard(i, Hand, Board);
}

//=========================================================
// discard the i'th card in the player's hand
// the card does not go to the graveyard, trigger leave play effects or anything else
void Player::discardCard(int i) {
    if (i<0 || i>= hand.size()) {
        throw runtime_error("invalid hand index to discard card");
    }
    hand.erase(hand.begin() + i);
}

//=========================================================
void Player::notifyGame(TriggerType triggerType, Notification notification) {
    game.notifyTopic(triggerType, notification);
}

//=========================================================
bool Player::moveCard(Card* card, Area src, Area dst) {
    for (int i = 0; i < areaToVec(src).size(); i++) {
        if (areaToVec(src)[i].get() == card) {
            return moveCard(i, src, dst);
        }
    }
    throw runtime_error("moveCard card not found.");
}

//=========================================================
bool Player::moveCard(int i, Area src, Area dst) { 
    if (src == dst) return false;
    // PRECOND: src.size() > i;
    auto card = areaToVec(src)[i].release();
    if (Minion* minion = dynamic_cast<Minion*> (card); minion) {
        if (src == Area::Board && dst != Area::Board) {
            // create notification 
            MinionNotification notification {minion, this};
            notifyGame(MinionLeave, notification);
        }
        if (src != Area::Board && dst == Area::Board) {
            MinionNotification notification {minion, this};
            notifyGame(MinionEnter, notification);
        }
        if (dst == Graveyard) {
            minion->removeAllEnchantments(std::nullopt);
        }
    }    
    // find the real unique pointer 
    auto& srcVec = areaToVec(src);
    auto& dstVec = areaToVec(dst);
    auto foundSrcCard = findCard(srcVec, card);
    if (foundSrcCard == srcVec.end()) {
        return false;
    }
    auto tempCard = std::move(*foundSrcCard);
    dstVec.push_back(std::move(tempCard));
    srcVec.erase(foundSrcCard);

    return true;
}

//=========================================================
std::unique_ptr<Card> Player::stealCard(int i, Area area) {
    // PRECOND: areaToVec(area).size() > i
    auto card = std::move(areaToVec(area)[i]);
    areaToVec(area).erase(areaToVec(area).begin() + i);
    return card;
}

//=========================================================
bool Player::modifyLife(int life) { 
    this->life += life;
    if (this->life <= 0) game.declareWin(!isPlayer1());
    return true;
}

//=========================================================
const vector<unique_ptr<Card>>& Player::getHand() const { return hand; }
const vector<unique_ptr<Card>>& Player::getDeck() const { return deck; }
const vector<unique_ptr<Card>>& Player::getBoard() const { return board; }
const vector<unique_ptr<Card>>& Player::getGraveyard() const { return graveyard; }

//=========================================================
bool Player::isPlayer1() const {
    return game.player1.get() == this;
}

//=========================================================
Player* Player::getOtherPlayer() const {
    return otherPlayer;
}

//=========================================================
void Player::setOtherPlayer(Player* player) {
    otherPlayer = player;
}

//=========================================================
// call after set other player
void Player::initializeDeck(const string& deckFilePath, bool shuffle) {
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
        } else {
            cout << "WARN: unknown card: " << card_string << endl;
        }
    }
    if (shuffle) shuffleDeck();

    // draw 5 cards from deck into hand
    for (int i=0;i<STARTING_NUM_CARDS;++i) {
        drawCard();
    }
}

//=========================================================
void Player::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

//=========================================================
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

//=========================================================
void Player::attachTrigger(TriggerType tt, Trigger* trigger) {
    game.attachTrigger(tt, trigger);
}

//=========================================================
std::vector<std::unique_ptr<Card>>& Player::areaToVec (Area area) {
    switch (area) {
        case Deck:
            return deck;
        case Board:
            return board;
        case Hand:
            return hand;
        default:
            return graveyard;
    }
}

//=========================================================
void Player::declareEnd() {
    auto notification = TurnChangeNotification(false, this);
    notifyGame(isPlayer1() ? EndTurnPlayer1 : EndTurnPlayer2, notification);
}

//=========================================================
void Player::declareStart() {
    auto notification = TurnChangeNotification(true, this);
    drawCard();
    notifyGame(isPlayer1() ? StartTurnPlayer1 : StartTurnPlayer2, notification);
    // now go through each of the minions in the board and check for start turn enchantments 
    for (auto& card : board) {
        Minion* minion = dynamic_cast<Minion*> (card.get());
        if (minion) {
            minion->setActions(1);
            minion->applyEnchantment(StartOfTurn);
        }
    }
    magic += 1;
}

//=========================================================
Ritual* Player::getRitual() const {
    return ritual.get();
}

//=========================================================
void Player::setRitual(std::unique_ptr<Ritual> ritual) {
    this->ritual = std::move(ritual);
}

//=========================================================
Card* Player::getGraveyardTop() const {
    if (graveyard.empty()) return nullptr;
    return graveyard.at(graveyard.size() - 1).get();
}

//=========================================================
int Player::getMagic() const {
    return magic;
}

//=========================================================
int Player::getLife() const {
    return life;
}

//=========================================================
const std::string& Player::getName() const {
    return name;
}

//=========================================================
void Player::setMagic(int magic) {
    this->magic = magic;
}