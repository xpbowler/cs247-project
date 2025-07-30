#include "cloner.h"
#include <helper.h>
#include <player.h>
#include <stdexcept>

//=========================================================
Cloner::Cloner(Player& owner, Player& opponent) 
    : ActivatedMinion{CLONER_ACTIVATION_COST, CLONER_ATK, CLONER_DEF, 
                      owner, opponent, CL, CLONER, CLONER_DESC, CLONER_COST} {}

//=========================================================
UseSkillStatus Cloner::useSkill(bool isTesting) {
    throw std::runtime_error("should not use skill for cloner");
}

//=========================================================
UseSkillStatus Cloner::useSkill(bool isTesting, Minion* minion) {
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
    if (magic < activationCost && !isTesting) {
        activationCost = oldActivationCost;
        return NotEnoughMagic;
    }
    summonMinion(minion->getType(), 2);
    actions--;
    if (isTesting) {
        owner.setMagic(std::max(0, magic - activationCost));
    }
    else {
        owner.setMagic(magic - activationCost);
    }
    activationCost = oldActivationCost;
    return OK;
}
