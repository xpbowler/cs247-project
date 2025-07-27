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
void MasterSummoner::useSkill()
{
    applyEnchantment(UseAbility);
    if (canUseAbility) summonMinion(AE, 3);
    canUseAbility = true;
}

