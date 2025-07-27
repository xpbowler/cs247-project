#include "fireElemental.h"
#include <notification.h>
#include <player.h>

//=========================================================
FireElemental::FireElemental(Player &owner, Player &opponent)
    : TriggeredMinion(FIRE_ELEMENTAL_ATK,
                      FIRE_ELEMENTAL_DEF,
                      owner, opponent, "Fire Elemental", FE)
{
    trigger = std::make_unique<Trigger> ();
    owner.attachTrigger(MinionEnter, trigger.get());
}

//=========================================================
void FireElemental::useSkill(Notification notification)
{
    // check if it is the correct notification
    auto realNoti = dynamic_cast<MinionNotification*> (&notification);
    if (!realNoti) return;
    // check if it is the same side, if so return
    if (realNoti->player == &owner) return;
    // now, use skill
    attackMinion(realNoti->minion, 1);
}
