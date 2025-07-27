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
UseSkillStatus NovicePyromancer::useSkill()
{
    std::cerr << "Novice Pyromancer should not use skill with no target. " << std::endl;
}


//=========================================================
UseSkillStatus NovicePyromancer::useSkill(Minion* minion) {
    if (actions < 1) {
        return NoAction;
    }
    applyEnchantment(UseAbility);
    if (!canUseAbility) {
        canUseAbility = true;
        return Silenced;
    } 
    attackMinion(minion, 1);
    actions--;
    return OK;
}