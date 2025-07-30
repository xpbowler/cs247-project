#include "banish.h"

//=========================================================
Banish::Banish(Player& owner, Player& opponent): Spell{BANISH_DESC, owner, opponent, BANISH, BANISH_COST} {
    
}

//=========================================================
bool Banish::action(std::variant<Minion*, Ritual*> card) {
    // BOARD -> GRAVEYARD
    // can act on both minion and rituals

    if (std::holds_alternative<Minion*>(card)) {
        Card* c = get<Minion*>(card);
        return c->getOwner().moveCard(c, Board, Graveyard);
    } else if (std::holds_alternative<Ritual*>(card)) {
        Card* c = get<Ritual*>(card);
        return c->getOwner().moveCard(c, Board, Graveyard);
    }
}
