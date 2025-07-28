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
    summonMinion(AE, 1);
    actions--;
    owner.setMagic(magic - activationCost);
    activationCost = oldActivationCost;
    return OK;
}

