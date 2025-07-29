#include "recharge.h"

using namespace std;

//=========================================================
Recharge::Recharge(Player& owner, Player& opponent): Spell{RECHARGE_DESC, owner, opponent, RECHARGE, RECHARGE_COST} {
    
}

//=========================================================
void Recharge::action(variant<Minion*, Ritual*> card) {
    if (holds_alternative<Ritual*>(card)) {
        get<Ritual*>(card)->setCharges(get<Ritual*>(card)->getCharges() + 3);
    }
}


