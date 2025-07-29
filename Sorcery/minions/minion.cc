#include "minion.h"
#include <player.h>
#include <baseEnchantment.h>
#include <enchantment.h>
#include <enchantmentDecorator.h>
#include <string>
#include <stdexcept>

//=========================================================
Minion::Minion(Player &owner, Player &opponent, int attack, int defence, MinionType minionType, const std::string& name, int cost) 
    : Card{owner, opponent, name, cost}, attack{attack}, defence{defence}, actions{0}, minionType{minionType}, enchantment{std::make_unique<BaseEnchantment>(owner, opponent)}
{

}

//=========================================================
int Minion::getDefence() { return defence; }

//=========================================================
int Minion::getAttack() { return attack; }

//=========================================================
int Minion::getActions() { return actions; }

//=========================================================
const std::vector<Enchantment*> Minion::getEnchantments() {
    std::vector<Enchantment*> result;
    Enchantment* currNode = enchantment.get();
    while (currNode) {
        if (auto decorator = dynamic_cast<EnchantmentDecorator*> (currNode); decorator) {
            result.push_back(decorator);
            currNode = decorator->getNext();
        }
        else {
            result.push_back(currNode);
            break;
        }
    }
    return result;
}

//=========================================================
void Minion::addEnchantment(std::unique_ptr<EnchantmentDecorator> newEnchantment) {
    newEnchantment->setNext(enchantment.release());
    enchantment = std::move(newEnchantment);
}

//=========================================================
bool Minion::removeTopEnchantment() {
    if (!enchantment) {
        return false;
    }
    auto decorator = dynamic_cast<EnchantmentDecorator*> (enchantment.get());
    if (!decorator) {
        // it is a base enchantment 
        enchantment.reset(nullptr);
        return true;
    }
    Enchantment* newChain = decorator->stealNext();
    enchantment.reset(newChain);
    return true;
}

//=========================================================
void Minion::setAttack(int attack) { this->attack = attack; }

//=========================================================
void Minion::setDefence(int defence) { this->defence = defence; }

//=========================================================
void Minion::heal(int hp) { defence += hp; }

//=========================================================
void Minion::takeDamage(int dmg) {
    defence -= dmg;
    if (defence <= 0) {
        dies();
    }
}

//=========================================================
void Minion::setActions(int action) {
    this->actions = action;
}

//=========================================================
bool Minion::attackMinion(Minion* minion, std::optional<int> dmg) {
    // check if there is enough action points 
    if (actions < 1) {
        return false;
    }
    // keep a copy of the old values
    int oldAttack = attack;
    int oldDefence = defence;
    applyEnchantment(Attack);
    minion->takeDamage(dmg ? *dmg : attack);
    attack = oldAttack;
    defence = oldDefence;
    return true;
}

//=========================================================
bool Minion::attackPlayer(std::optional<int> dmg) {
    // check if there is enough action points 
    if (actions < 1) {
        return false;
    }
    int oldAttack = attack;
    int oldDefence = defence;
    applyEnchantment(Attack);
    opponent.modifyLife(dmg ? -*dmg : -attack);
    attack = oldAttack;
    defence = oldDefence;
    return true;
}

//=========================================================
void Minion::gainStats(int attack, int defence) {
    this->attack += attack;
    this->defence += defence;
}

//=========================================================
void Minion::summonMinion(MinionType minionType, int amount) {
    owner.summonMinion(minionType, amount);
}

//=========================================================
void Minion::dies() {
    owner.moveCard(this, Board, Graveyard);
}


Minion::~Minion() {}

//=========================================================
void Minion::removeAllEnchantments(std::optional<EnchantmentTiming> et) {
    if (!et) {
        enchantment.reset(nullptr);
        return;
    }
    if (!enchantment) return;
    while (enchantment && enchantment->getTiming() == *et) {
        removeTopEnchantment();
    }
    Enchantment* currNode = enchantment.get();
    Enchantment* prevNode = nullptr;
    while (currNode) {
        auto currBase = dynamic_cast<BaseEnchantment*> (currNode);
        auto currDecorator = dynamic_cast<EnchantmentDecorator*> (currNode);
        if (currNode->getTiming() == *et) {
            if (!prevNode) throw std::runtime_error("previous node is somehow nullptr while removing enchantments");
            // if it is base enchantment then we exit 
            
            auto prevDecorator = dynamic_cast<EnchantmentDecorator*> (prevNode);
            // prev node must be not null
            if (currBase) {
                prevDecorator->setNext(nullptr);
            }
            else {
                prevDecorator->setNext(currDecorator->stealNext());
            }
            currNode = prevDecorator->getNext();
        }
        else {
            if (currBase) break;
            prevNode = currNode;
            currNode = currDecorator->getNext();
        }
    }
}

//=========================================================
void Minion::applyEnchantment(EnchantmentTiming et) {
    enchantment->apply(*this, et);
}
