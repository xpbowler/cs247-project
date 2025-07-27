#include "boneGolem.h"
#include <notification.h>

//=========================================================
BoneGolem::BoneGolem(Player &owner, Player &opponent)
    : TriggeredMinion(BONE_GOLEM_ATK,
                      BONE_GOLEM_DEF,
                      owner, opponent, "Bone Golem", BG)
{
    // TODO: set up trigger
}

//=========================================================
void BoneGolem::useSkill(Notification notification)
{
    // TODO
}
