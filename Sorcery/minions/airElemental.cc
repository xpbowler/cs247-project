#include "airElemental.h"
#include <helper.h>

//=========================================================
AirElemental::AirElemental(Player& owner, Player& opponent) 
    : BaseMinion {AIR_ELEMENTAL_ATK,
                  AIR_ELEMENTAL_DEF, 
                  owner, opponent, AIR_ELEMENTAL, AIR_ELEMENTAL_COST, AE} {}


