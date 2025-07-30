#include "recharge.h"

using namespace std;

//=========================================================
Recharge::Recharge(Player& owner, Player& opponent): Spell{RECHARGE_DESC, owner, opponent, RECHARGE, RECHARGE_COST} {
    
}

//=========================================================
// card should be the ritual that gains 3 charges
bool Recharge::action(variant<Minion*, Ritual*> card) {
    if (holds_alternative<Ritual*>(card)) {
        get<Ritual*>(card)->setCharges(get<Ritual*>(card)->getCharges() + 3);
        return true;
    }
    return false;
}
