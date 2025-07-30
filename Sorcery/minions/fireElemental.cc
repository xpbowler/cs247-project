#include "fireElemental.h"
#include <notification.h>
#include <player.h>

//=========================================================
FireElemental::FireElemental(Player &owner, Player &opponent)
    : TriggeredMinion(FIRE_ELEMENTAL_ATK,
                      FIRE_ELEMENTAL_DEF,
                      owner, opponent, 
                      FIRE_ELEMENTAL, FIRE_ELEMENTAL_DESC, MinionEnter, FIRE_ELEMENTAL_COST, FE)
{
    trigger = std::make_unique<Trigger> (this);
}

//=========================================================
void FireElemental::useSkill(const Notification& notification)
{
    // check if it is the correct notification
    auto realNoti = dynamic_cast<const MinionNotification*> (&notification);
    if (!realNoti) return;
    // check if it is the same side, if so return
    if (realNoti->player == &owner) return;
    // now, use skill
    applyEnchantment(UseAbility);
    if (canUseAbility) attackMinion(realNoti->minion, 1);
    canUseAbility = true;
}
