#include "raiseDead.h"
#include <minion.h>

//=========================================================
RaiseDead::RaiseDead(Player& owner, Player& opponent): Spell{RAISE_DEAD_DESC, owner, opponent, RAISE_DEAD, RAISE_DEAD_COST} {
    
}

//=========================================================
bool RaiseDead::action(std::variant<Minion*, Ritual*>) {
    // ASSUMING GRAVEYARD -> BOARD
    auto card = owner.getGraveyardTop();
    if (!card) {
        std::cout << "There is nothing in the graveyard while performing Raise Dead." << std::endl;
        return false;
    }
    if (owner.getBoard().size() >= 5) {
        throw std::runtime_error("raisedead: board is already full and cant put back a card from graveyard");
    }
    Minion* m = dynamic_cast<Minion*>(card);
    m->setDefence(1);
    owner.moveCard(card, Graveyard, Board);
    return true;
}

