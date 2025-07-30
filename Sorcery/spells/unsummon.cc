#include "unsummon.h"

//=========================================================
Unsummon::Unsummon(Player& owner, Player& opponent): Spell{UNSUMMON_DESC, owner, opponent, UNSUMMON, UNSUMMON_COST} {
    
}

//=========================================================
bool Unsummon::action(std::variant<Minion*, Ritual*> card) {
    // ASSUMING BOARD -> HAND
    if (holds_alternative<Minion*>(card)) { // can only unsummon minions
        Card* m = get<Minion*>(card);
        return m->getOwner().moveCard(m, Board, Hand);
    }
    return false;
}
