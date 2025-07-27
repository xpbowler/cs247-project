#include "earthElemental.h"

//=========================================================
EarthElemental::EarthElemental(Player &owner, Player &opponent)
    : BaseMinion(EARTH_ELEMENTAL_ATK,
                 EARTH_ELEMENTAL_DEF,
                 owner, opponent, "Earth Elemental", EE)
{
    
}
