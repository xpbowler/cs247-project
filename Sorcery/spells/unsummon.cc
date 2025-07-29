#include "unsummon.h"

//=========================================================
Unsummon::Unsummon(Player& owner, Player& opponent): Spell{UNSUMMON_DESC, owner, opponent, UNSUMMON, UNSUMMON_COST} {
    
}

//=========================================================
void Unsummon::action(std::variant<Minion*, Ritual*> card) {
    // ASSUMING BOARD -> HAND
    if (holds_alternative<Minion*>(card)) {
        if (!owner.moveCard(get<Minion*>(card), Board, Hand)) {
            opponent.moveCard(get<Minion*>(card), Board, Hand);
        }
    }
}
