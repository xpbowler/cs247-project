#include "minion.h"
#include <player.h>
#include <enchantment.h>
#include <enchantmentDecorator.h>
#include <string>
#include <stdexcept>

//=========================================================
Minion::Minion(Player &owner, Player &opponent, int attack, int defence, MinionType minionType, std::string name) 
    : Card{owner, opponent}, attack{attack}, defence{defence}, actions{0}, minionType{minionType}, enchantment{nullptr}, name {name}
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
}

//=========================================================
void Minion::addEnchantment(std::unique_ptr<EnchantmentDecorator> newEnchantment) {
    newEnchantment->setNext(enchantment.release());
    enchantment = std::move(newEnchantment);
}

//=========================================================
void Minion::removeTopEnchantment() {
    if (!enchantment) {
        throw std::runtime_error ("This minion has no enchantments.");
        return;
    }
    auto decorator = dynamic_cast<EnchantmentDecorator*> (enchantment.get());
    if (!decorator) {
        // it is a base enchantment 
        enchantment.reset(nullptr);
        return;
    }
    Enchantment* newChain = decorator->stealNext();
    enchantment.reset(newChain);
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
void Minion::setAction(int action) {
    this->actions = action;
}

//=========================================================
void Minion::attackMinion(Minion* minion, int dmg) {
    // keep a copy of the old values
    int oldAttack = attack;
    int oldDefence = defence;
    applyEnchantment(Attack);
    minion->takeDamage(dmg);
    attack = oldAttack;
    defence = oldDefence;
}

//=========================================================
void Minion::attackPlayer(int dmg) {
    opponent.modifyLife(-dmg);
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
    // TODO
    // need to implement logic for triggers? 
    // need to activate its triggers, if any, before dying
}


Minion::~Minion() {}