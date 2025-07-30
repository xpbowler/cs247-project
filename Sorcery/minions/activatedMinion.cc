#include "activatedMinion.h"

//=========================================================
ActivatedMinion::ActivatedMinion(int activationCost, 
                                 int attack, 
                                 int defence, 
                                 Player& owner,
                                 Player& opponent, 
                                 MinionType minionType,
                                 std::string name,
                                 std::string description,
                                 int cost
                                )
                                 : Minion {owner, opponent, attack, defence, minionType, name, cost}, 
                                 activationCost {activationCost},
                                 description{std::move(description)},
                                 canUseAbility {true} {

}


//=========================================================
int ActivatedMinion::getActivationCost() const { return activationCost; }

//=========================================================
void ActivatedMinion::setActivationCost(int cost) { this->cost = cost; }

//=========================================================
void ActivatedMinion::disableAbility() {
    canUseAbility = false;
}

//=========================================================
const std::string& ActivatedMinion::getDescription() const {
    return description;
}