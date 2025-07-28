#include "disenchant.h"

//=========================================================
Disenchant::Disenchant(Player& owner, Player& opponent): Spell{DISENCHANT_DESC, owner, opponent} {

}

//=========================================================
void Disenchant::action(std::variant<Minion*, Ritual*> card) {
    if (holds_alternative<Minion*>(card)) {
        get<Minion*>(card)->removeTopEnchantment();
    }
}