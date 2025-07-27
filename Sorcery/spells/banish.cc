#include "banish.h"

//=========================================================
Banish::Banish(Player& owner, Player& opponent): Spell{BANISH_DESC, owner, opponent} {
    // TODO 
}

//=========================================================
void Banish::action(std::variant<Minion*, Ritual*> card) {
    // ASSUMING BOARD -> GRAVEYARD
    if (holds_alternative<Minion*>(card)) {
        if (!owner.moveCard(get<Minion*>(card), Board, Graveyard)) {
            opponent.moveCard(get<Minion*>(card), Board, Graveyard);
        }
    }
}

