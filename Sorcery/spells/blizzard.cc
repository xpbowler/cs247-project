#include "blizzard.h"

//=========================================================
Blizzard::Blizzard(Player& owner, Player& opponent): Spell{BLIZZARD_DESC, owner, opponent, BLIZZARD, BLIZZARD_COST} {
    
}

//=========================================================
void Blizzard::action(std::variant<Minion*, Ritual*> card) {
    for (const std::unique_ptr<Card>& c : owner.getBoard()) {
        if (dynamic_cast<Minion*>(c.get())) {
            dynamic_cast<Minion*>(c.get())->takeDamage(2);
        }
    }
    for (const std::unique_ptr<Card>& c : opponent.getBoard()) {
        if (dynamic_cast<Minion*>(c.get())) {
            dynamic_cast<Minion*>(c.get())->takeDamage(2);
        }
    }
}

