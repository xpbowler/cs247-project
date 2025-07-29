#include "giantStrength.h"
#include <helper.h>
#include <minion.h>

//=============================================================
GiantStrength::GiantStrength(Player& owner, Player& opponent) 
    : EnchantmentDecorator {GIANT_STRENGTH_DESC, owner, opponent, Attack, GIANT_STRENGTH, GIANT_STRENGTH_COST} {}

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
