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
    auto minion = dynamic_cast<Minion*> (card); 
    if (!minion) {
        throw std::runtime_error("Raise dead sees that graveyard top is somehow not a minion");
    }
    minion->setDefence(1);
    owner.moveCard(minion, Graveyard, Board);
    return true;
    
}

