#include "magicFatigue.h"
#include <util.h>
#include <activatedMinion.h>

//=========================================================
MagicFatigue::MagicFatigue(Player& owner, Player& opponent)
    : EnchantmentDecorator {"Magic Fatigue", owner, opponent, UseAbility} {}

//=========================================================
void MagicFatigue::apply(Minion& minion, EnchantmentTiming et) {
    next->apply(minion, et);
    auto activatedMinion = dynamic_cast<ActivatedMinion*> (&minion);
    if (et == timing && activatedMinion) {
        int cost = activatedMinion->getActivationCost();
        activatedMinion->setActivationCost(cost + 2);
    }
}

