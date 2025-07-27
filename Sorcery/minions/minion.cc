#include "minion.h"
#include <player.h>
#include <string>

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
void Minion::setAttack(int attack) { this->attack = attack; }

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
    minion->takeDamage(dmg);
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