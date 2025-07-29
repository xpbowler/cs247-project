#include "enrage.h"
#include <helper.h>
#include <minion.h>

//========================================================================
Enrage::Enrage(Player& owner, Player& opponent)
    : EnchantmentDecorator(ENRAGE_DESC, owner, opponent, Attack, ENRAGE, ENRAGE_COST) {}

//========================================================================
void Enrage::apply(Minion& minion, EnchantmentTiming et) {
    next->apply(minion, et);
    if (et == timing) {
        int attack = minion.getAttack();
        minion.setAttack(2 * attack);
        int defence = minion.getDefence();
        minion.setDefence(2 * defence);
    }
}
