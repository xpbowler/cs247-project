#include "masterSummoner.h"
#include "player.h"

//=========================================================
MasterSummoner::MasterSummoner(Player &owner, Player &opponent)
    : ActivatedMinion(MASTER_SUMMONER_ACTIVATION_COST,
                      MASTER_SUMMONER_ATK,
                      MASTER_SUMMONER_DEF,
                      owner, opponent, MS, "Master Summoner")
{
}

//=========================================================
UseSkillStatus MasterSummoner::useSkill()
{
    if (actions < 1) {
        return NoAction;
    }
    applyEnchantment(UseAbility);
    if (!canUseAbility) {
        canUseAbility = true;
        return Silenced;
    } 
    summonMinion(AE, 3);
    actions--;
    return OK;
}

