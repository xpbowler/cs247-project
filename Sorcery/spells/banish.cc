#include "banish.h"

//=========================================================
Banish::Banish(Player& owner, Player& opponent): Spell{BANISH_DESC, owner, opponent} {
    
}

//=========================================================
void Banish::action(std::variant<Minion*, Ritual*> card) {
    // ASSUMING BOARD -> GRAVEYARD (Could maybe also make minion take dmg?)
    if (holds_alternative<Minion*>(card)) {
        if (!owner.moveCard(get<Minion*>(card), Board, Graveyard)) {
            opponent.moveCard(get<Minion*>(card), Board, Graveyard);
        }
    } else if (holds_alternative<Ritual*>(card)) {
        if (!owner.moveCard(get<Ritual*>(card), Board, Graveyard)) {
            opponent.moveCard(get<Ritual*>(card), Board, Graveyard);
        }
    }
}

