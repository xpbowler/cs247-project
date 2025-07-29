#include "silence.h"
#include "helper.h"
#include "activatedMinion.h"

//=========================================================
Silence::Silence(Player& owner, Player& opponent)
    : EnchantmentDecorator {"Silence", owner, opponent, UseAbility} {}

//=========================================================
void Silence::apply(Minion& minion, EnchantmentTiming et) {
    next->apply(minion, et);
    auto activatedMinion = dynamic_cast<ActivatedMinion*> (&minion);
    if (activatedMinion && et == timing) {
        activatedMinion->disableAbility();
    }
}
