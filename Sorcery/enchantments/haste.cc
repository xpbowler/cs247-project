#include "haste.h"
#include <minion.h>

//========================================================
Haste::Haste(Player& owner, Player& opponent) 
    : EnchantmentDecorator(HASTE_DESC, owner, opponent, StartOfTurn, HASTE, HASTE_COST) {}

//========================================================
void Haste::apply(Minion& minion, EnchantmentTiming et) {
    next->apply(minion, et);
    if (et == timing) {
        int actions = minion.getActions();
        minion.setActions(actions + 1);
    }
}
