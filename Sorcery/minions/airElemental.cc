#include "airElemental.h"

//=========================================================
AirElemental::AirElemental(Player& owner, Player& opponent) 
    : BaseMinion {AIR_ELEMENTAL_ATK,
                  AIR_ELEMENTAL_DEF, 
                  owner, opponent, "Air Elemental", AE} {}


