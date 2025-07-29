#include "magicFatigue.h"
#include "activatedMinion.h"
#include <helper.h>

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

