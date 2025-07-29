#include "silence.h"
#include <activatedMinion.h>
#include <helper.h>

//=========================================================
Silence::Silence(Player& owner, Player& opponent)
    : EnchantmentDecorator {SILENCE_DESC, owner, opponent, UseAbility, SILENCE, SILENCE_COST} {}

//=========================================================
void Silence::apply(Minion& minion, EnchantmentTiming et) {
    next->apply(minion, et);
    auto activatedMinion = dynamic_cast<ActivatedMinion*> (&minion);
    if (activatedMinion && et == timing) {
        activatedMinion->disableAbility();
    }
}
