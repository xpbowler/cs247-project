#include "haste.h"
#include "minion.h"

//========================================================
Haste::Haste(Player& owner, Player& opponent) 
    : EnchantmentDecorator("Haste", owner, opponent, StartOfTurn) {}

//========================================================
void Haste::apply(Minion& minion, EnchantmentTiming et) {
    next->apply(minion, et);
    if (et == timing) {
        int actions = minion.getActions();
        minion.setActions(actions + 1);
    }
}
