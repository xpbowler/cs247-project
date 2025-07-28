#include "giantStrength.h"
#include <util.h>
#include <minion.h>

//=============================================================
GiantStrength::GiantStrength(Player& owner, Player& opponent) 
    : EnchantmentDecorator {"Giant Strength", owner, opponent, Attack} {}

//=============================================================
void GiantStrength::apply(Minion& minion, EnchantmentTiming et) {
    next->apply(minion, et);
    if (et == timing) {
        int attack = minion.getAttack();
        minion.setAttack(attack + 2);
        int defence = minion.getDefence();
        minion.setDefence(defence + 2); 
    }
}
