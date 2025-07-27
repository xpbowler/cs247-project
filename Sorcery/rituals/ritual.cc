#include "ritual.h"
#include <trigger.h>

//=========================================================
int Ritual::getCharges() const { return charges; }

//=========================================================
void Ritual::setCharges(int charges) { this->charges = charges; }

//=========================================================
Ritual::Ritual(int cost, int charges, Player& owner, Player& opponent) : activationCost {cost}, charges{charges}, Card {owner, opponent} {
    trigger = std::make_unique<Trigger> ();
}

// the subclasses have the responsibility of setting up the trigger for the correct trigger topic 

