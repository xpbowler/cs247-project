#include "ritual.h"
#include "../triggers/trigger.h"

using namespace std;

//=========================================================
int Ritual::getCharges() const { return charges; }

//=========================================================
void Ritual::setCharges(int charges) { this->charges = charges; }

//=========================================================
int Ritual::getActivationCost() const { return activationCost; }

//=========================================================
Ritual::Ritual(int cost, int charges, Player& owner, Player& opponent, const string& description) 
    : Card {owner, opponent}, activationCost {cost}, charges{charges}, description{description} {
    trigger = std::make_unique<Trigger> (this);
}

const string& Ritual::get_description() const {
    return description;
}

// the subclasses have the responsibility of setting up the trigger for the correct trigger topic 

