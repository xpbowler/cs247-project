#include "raiseDead.h"

//=========================================================
RaiseDead::RaiseDead(Player& owner, Player& opponent): Spell{RAISE_DEAD_DESC, owner, opponent} {
    // TODO 
}

//=========================================================
void RaiseDead::action(std::variant<Minion*, Ritual*> card) {
    // ASSUMING GRAVEYARD -> BOARD
    if (holds_alternative<Minion*>(card)) {
        get<Minion*>(card)->setDefence(1);
        if (!owner.moveCard(get<Minion*>(card), Graveyard, Board)) {
            opponent.moveCard(get<Minion*>(card), Graveyard, Board);
        }
    }
}

