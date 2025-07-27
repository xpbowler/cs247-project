#include "novicePyromancer.h"
#include <iostream>

//=========================================================
NovicePyromancer::NovicePyromancer(Player &owner, Player &opponent)
    : ActivatedMinion(NOVICE_PYROMANCER_ACTIVATION_COST,
                      NOVICE_PYROMANCER_ATK,
                      NOVICE_PYROMANCER_DEF,
                      owner, opponent, NP, "Novice Pyromancer")
{

}

//=========================================================
void NovicePyromancer::useSkill()
{
    std::cerr << "Novice Pyromancer should not use skill with no target. " << std::endl;
}


//=========================================================
void NovicePyromancer::useSkill(Minion* minion) {
    applyEnchantment(UseAbility);
    if (canUseAbility) attackMinion(minion, 1);
    canUseAbility = true;
}