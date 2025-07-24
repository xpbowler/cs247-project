#include "ritual.h"

//=========================================================
int Ritual::getCharges() const { return charges; }

//=========================================================
void Ritual::setCharges(int charges) { this->charges = charges; }

//=========================================================
Ritual::Ritual(int cost, int charges) : activationCost {cost}, charges{charges} {}

// the subclasses have the responsibility of setting up the trigger for the correct trigger topic 

