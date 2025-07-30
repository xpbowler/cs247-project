#include "disenchant.h"

//=========================================================
Disenchant::Disenchant(Player& owner, Player& opponent): Spell{DISENCHANT_DESC, owner, opponent, DISENCHANT, DISENCHANT_COST} {

}

//=========================================================
bool Disenchant::action(std::variant<Minion*, Ritual*> card) {
    if (holds_alternative<Minion*>(card)) {
        return get<Minion*>(card)->removeTopEnchantment();
    }
    return false;
}
