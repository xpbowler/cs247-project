#include "banish.h"

//=========================================================
Banish::Banish(Player& owner, Player& opponent): Spell{BANISH_DESC, owner, opponent, BANISH, BANISH_COST} {
    
}

//=========================================================
bool Banish::action(std::variant<Minion*, Ritual*> card) {
    // ASSUMING BOARD -> GRAVEYARD (Could maybe also make minion take dmg?)
    if (holds_alternative<Minion*>(card)) {
        if (!owner.moveCard(get<Minion*>(card), Board, Graveyard)) {
            return opponent.moveCard(get<Minion*>(card), Board, Graveyard);
        }
        return true;
    } else if (holds_alternative<Ritual*>(card)) {
        if (!owner.moveCard(get<Ritual*>(card), Board, Graveyard)) {
            return opponent.moveCard(get<Ritual*>(card), Board, Graveyard);
        }
        return true;
    }
}

