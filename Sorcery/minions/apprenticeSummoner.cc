#include "apprenticeSummoner.h"
#include "player.h"

//=========================================================
ApprenticeSummoner::ApprenticeSummoner(Player& owner, Player& opponent) 
    : ActivatedMinion (APPRENTICE_SUMMONER_ACTIVATION_COST,
                       APPRENTICE_SUMMONER_ATK, 
                       APPRENTICE_SUMMONER_DEF,
                       owner, opponent, AS, "Apprentice Summoner") {

}


//=========================================================
UseSkillStatus ApprenticeSummoner::useSkill() {
    if (actions < 1) {
        return NoAction;
    }
    applyEnchantment(UseAbility);
    if (!canUseAbility) {
        canUseAbility = true;
        return Silenced;
    }
    summonMinion(AE, 1);
    actions--;
    return OK;
}

