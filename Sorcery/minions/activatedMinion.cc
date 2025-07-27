#include "activatedMinion.h"

//=========================================================
ActivatedMinion::ActivatedMinion(int activationCost, 
                                 int attack, 
                                 int defence, 
                                 Player& owner,
                                 Player& opponent, 
                                 MinionType minionType,
                                 std::string name) : Minion {owner, opponent, attack, defence, minionType, name}, activationCost {activationCost} {

}


//=========================================================
int ActivatedMinion::getActivationCost() const { return activationCost; }