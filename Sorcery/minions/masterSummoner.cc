#include "masterSummoner.h"
#include <player.h>

//=========================================================
MasterSummoner::MasterSummoner(Player &owner, Player &opponent)
    : ActivatedMinion(MASTER_SUMMONER_ACTIVATION_COST,
                      MASTER_SUMMONER_ATK,
                      MASTER_SUMMONER_DEF,
                      owner, opponent, MS, MASTER_SUMMONER, MASTER_SUMMONER_DESC, MASTER_SUMMONER_COST)
{
}

//=========================================================
UseSkillStatus MasterSummoner::useSkill()
{
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
    summonMinion(AE, 3);
    actions--;
    owner.setMagic(magic - activationCost);
    activationCost = oldActivationCost;
    return OK;
}

