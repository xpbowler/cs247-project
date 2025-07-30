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
#include <enrage.h>
#include <haste.h>
#include <cloner.h>
#include <notification.h>


#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
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
Player::Player(string& name, Game* game): name{std::move(name)}, 
                                          life{STARTING_LIFE}, 
                                          magic{STARTING_MAGIC},
                                          isFirstTurn{true}, 
                                          deck{}, 
                                          hand{}, 
                                          board{}, 
                                          graveyard{}, 
                                          ritual{}, 
                                          otherPlayer{nullptr}, 
                                          game{*game} {}

//=========================================================
// draw command draws a card, similar to the effect if the player just started their turn
void Player::drawCard() {
    if (deck.empty() || hand.size()>=5) return;
    unique_ptr<Card> card = std::move(deck.front());
    deck.erase(deck.begin());
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
    if (i<0 || (size_t)i>= hand.size()) {
        throw runtime_error("invalid hand index to discard card");
    }
    hand.erase(hand.begin() + i);
}

//=========================================================
void Player::notifyGame(TriggerType triggerType, const Notification& notification) {
    game.notifyTopic(triggerType, notification);
}

std::string areaToString(Area a) {
    if (a==Area::Board) return "board";
    else if (a==Area::Hand) return "hand";
    else if (a==Area::Deck) return "deck";
    else /* if (a==Area::Graveyard) */ return "graveyard";
}

//=========================================================
bool Player::moveCard(Card* card, Area src, Area dst) {
    vector<unique_ptr<Card>>& src_area = areaToVec(src);
    for (size_t i = 0; i < src_area.size(); ++i) {
        if (src_area.at(i).get() == card) {
            return moveCard(i, src, dst);
        }
    }
    throw runtime_error("moveCard card not found. src: " + areaToString(src) + ". dst: " + areaToString(dst) + ". card: " + card->get_name());
}

//=========================================================
bool Player::moveCard(int i, Area src, Area dst) { 
    // PRECOND: src.size() > i;
    if (src == dst) return false;

    auto card = areaToVec(src)[i].get();

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

    if (src != Area::Board && dst == Area::Board) {
        if (auto minion = dynamic_cast<TriggeredMinion*> (card)) {
            attachTrigger(minion->getTriggerType(), &minion->getTrigger());
        }
    }

    
    if (Minion* minion = dynamic_cast<Minion*> (card); minion) {
        if (src == Area::Board && dst != Area::Board) {
            // create notification 
            MinionNotification notification {minion, this};
            notifyGame(MinionLeave, notification);
            minion->removeAllEnchantments(std::nullopt);
        }
        if (src != Area::Board && dst == Area::Board) {
            MinionNotification notification {minion, this};
            minion->setActions(1);
            notifyGame(MinionEnter, notification);
        }
    }    

    if (src == Area::Board && dst != Area::Board) {
        if (auto minion = dynamic_cast<TriggeredMinion*> (card)) {
            minion->detachTrigger();
        }
        if (auto ritual = dynamic_cast<Ritual*> (card)) {
            ritual->detachTrigger();
        }
    }
    

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
    using Maker = std::function<std::unique_ptr<Card>(Player&, Player&)>;
    static const std::unordered_map<std::string, Maker> make = {
        {"Air Elemental",        [](Player& a, Player& b){ return std::make_unique<AirElemental>(a,b); }},
        {"Earth Elemental",      [](Player& a, Player& b){ return std::make_unique<EarthElemental>(a,b); }},
        {"Fire Elemental",       [](Player& a, Player& b){ return std::make_unique<FireElemental>(a,b); }},
        {"Potion Seller",        [](Player& a, Player& b){ return std::make_unique<PotionSeller>(a,b); }},
        {"Novice Pyromancer",    [](Player& a, Player& b){ return std::make_unique<NovicePyromancer>(a,b); }},
        {"Apprentice Summoner",  [](Player& a, Player& b){ return std::make_unique<ApprenticeSummoner>(a,b); }},
        {"Bone Golem",           [](Player& a, Player& b){ return std::make_unique<BoneGolem>(a,b); }},
        {"Master Summoner",      [](Player& a, Player& b){ return std::make_unique<MasterSummoner>(a,b); }},
        {"Banish",               [](Player& a, Player& b){ return std::make_unique<Banish>(a,b); }},
        {"Unsummon",             [](Player& a, Player& b){ return std::make_unique<Unsummon>(a,b); }},
        {"Recharge",             [](Player& a, Player& b){ return std::make_unique<Recharge>(a,b); }},
        {"Disenchant",           [](Player& a, Player& b){ return std::make_unique<Disenchant>(a,b); }},
        {"Raise Dead",           [](Player& a, Player& b){ return std::make_unique<RaiseDead>(a,b); }},
        {"Blizzard",             [](Player& a, Player& b){ return std::make_unique<Blizzard>(a,b); }},
        {"Giant Strength",       [](Player& a, Player& b){ return std::make_unique<GiantStrength>(a,b); }},
        {"Magic Fatigue",        [](Player& a, Player& b){ return std::make_unique<MagicFatigue>(a,b); }},
        {"Silence",              [](Player& a, Player& b){ return std::make_unique<Silence>(a,b); }},
        {"Dark Ritual",          [](Player& a, Player& b){ return std::make_unique<DarkRitual>(a,b); }},
        {"Aura of Power",        [](Player& a, Player& b){ return std::make_unique<AuraOfPower>(a,b); }},
        {"Standstill",           [](Player& a, Player& b){ return std::make_unique<Standstill>(a,b); }},
        {"Enrage",               [](Player& a, Player& b){ return std::make_unique<Enrage>(a,b); }},
        {"Haste",                [](Player& a, Player& b){ return std::make_unique<Haste>(a,b); }},
        {"Cloner",               [](Player& a, Player& b){ return std::make_unique<Cloner>(a,b); }},
    };

    // Bonus cards
    static const char* bonusCards[] = {CLONER};
    
    while (getline(initFile, card_string)) {
        if (auto it = make.find(card_string); it != make.end()) {
            for (auto& x : bonusCards) {
                if (!game.isBonusFeatures() && card_string==x) {
                    // if bonus features are not enabled, skip over the bonus cards
                    cout << "Unable to use bonus card when bonus features is not enabled" << endl;
                    continue;
                }
            }
            deck.push_back(it->second(*this, *otherPlayer));
        } else std::cout << "WARN: unknown card: " << card_string << '\n';
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
void Player::summonMinion(MinionType type, int amount) {
    using Maker = std::function<std::unique_ptr<Card>(Player&, Player&)>;
    static const std::array<Maker, NUM_MINION_TYPES> kMake = {
        /* AE */ [](Player& a, Player& b){ return std::make_unique<AirElemental>(a, b); },
        /* EE */ [](Player& a, Player& b){ return std::make_unique<EarthElemental>(a, b); },
        /* NP */ [](Player& a, Player& b){ return std::make_unique<NovicePyromancer>(a, b); },
        /* MS */ [](Player& a, Player& b){ return std::make_unique<MasterSummoner>(a, b); },
        /* AS */ [](Player& a, Player& b){ return std::make_unique<ApprenticeSummoner>(a, b); },
        /* BG */ [](Player& a, Player& b){ return std::make_unique<BoneGolem>(a, b); },
        /* FE */ [](Player& a, Player& b){ return std::make_unique<FireElemental>(a, b); },
        /* PS */ [](Player& a, Player& b){ return std::make_unique<PotionSeller>(a, b); },
        /* CL */ [](Player& a, Player& b){ return std::make_unique<Cloner>(a, b); },
    };
    
    // Guard against underflow and mixed signed/unsigned:
    int freeSlots = std::max(0, 5 - static_cast<int>(board.size()));
    int n = std::max(0, std::min(freeSlots, amount));

    auto idx = static_cast<size_t>(type);
    if (idx >= kMake.size()) return; // unknown type

    for (int i = 0; i < n; ++i) {
        board.push_back(kMake[idx](*this, *otherPlayer));
        // need to send a notification for minion entering
        if (auto minion = dynamic_cast<Minion*> (board[board.size() - 1].get())) {
            MinionNotification notification {minion, this};
            notifyGame(MinionEnter, notification);
        }
        else {
            throw runtime_error("Unit summoned is somehow not a minion.");
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
    if (!isFirstTurn) {
        magic += 1;
    }
    isFirstTurn = false;
}

//=========================================================
Ritual* Player::getRitual() const {
    return ritual.get();
}

//=========================================================
void Player::setRitual(std::unique_ptr<Ritual> newRitual) {
    if (ritual) ritual->detachTrigger();
    ritual = std::move(newRitual);
    attachTrigger(ritual->getTriggerType(), &ritual->getTrigger());
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
