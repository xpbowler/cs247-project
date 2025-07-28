#include "novicePyromancer.h"
#include <iostream>
#include <stdexcept>
#include <player.h>

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
    throw std::runtime_error("should not use skill for novice pyromancer");
}


//=========================================================
UseSkillStatus NovicePyromancer::useSkill(Minion* minion) {
    if (actions < 1) {
        return NoAction;
    }
    int oldActivationCost = activationCost;
    applyEnchantment(UseAbility);
    if (!canUseAbility) {
        canUseAbility = true;
        activationCost = oldActivationCost;
        return Silenced;
    } 
    int magic = owner.getMagic();
    if (magic < activationCost) {
        activationCost = oldActivationCost;
        return NotEnoughMagic;
    }
    attackMinion(minion, 1);
    actions--;
    owner.setMagic(magic - activationCost);
    activationCost = oldActivationCost;
    return OK;
}