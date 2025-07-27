#include "boneGolem.h"
#include <notification.h>
#include <player.h>

//=========================================================
BoneGolem::BoneGolem(Player &owner, Player &opponent)
    : TriggeredMinion(BONE_GOLEM_ATK,
                      BONE_GOLEM_DEF,
                      owner, opponent, "Bone Golem", BG)
{
    trigger = std::make_unique<Trigger> (this);
    owner.attachTrigger(MinionLeave, trigger.get());
}

//=========================================================
void BoneGolem::useSkill(Notification)
{
    gainStats(1, 1);
}
