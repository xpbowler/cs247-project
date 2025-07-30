#include "boneGolem.h"
#include <notification.h>
#include <player.h>

//=========================================================
BoneGolem::BoneGolem(Player &owner, Player &opponent)
    : TriggeredMinion(BONE_GOLEM_ATK,
                      BONE_GOLEM_DEF,
                      owner, opponent, 
                      BONE_GOLEM, BONE_GOLEM_DESC, MinionLeave, BONE_GOLEM_COST, BG)
{
    trigger = std::make_unique<Trigger> (this);
}

//=========================================================
void BoneGolem::useSkill(const Notification&)
{
    applyEnchantment(UseAbility);
    if (canUseAbility) gainStats(1, 1);
    canUseAbility = true;
}
