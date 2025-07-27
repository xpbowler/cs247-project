#include "fireElemental.h"
#include <notification.h>

//=========================================================
FireElemental::FireElemental(Player &owner, Player &opponent)
    : TriggeredMinion(FIRE_ELEMENTAL_ATK,
                      FIRE_ELEMENTAL_DEF,
                      owner, opponent, "Fire Elemental", FE)
{
    // TODO: set up trigger
}

//=========================================================
void FireElemental::useSkill(Notification notification)
{
    // TODO
}
