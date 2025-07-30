#include "ritual.h"
#include "../triggers/trigger.h"

using namespace std;

//=========================================================
int Ritual::getCharges() const { return charges; }

//=========================================================
void Ritual::setCharges(int charges) { this->charges = charges; }

//=========================================================
Trigger& Ritual::getTrigger() const {
    return *trigger;
}

//=========================================================
const TriggerType Ritual::getTriggerType() const {
    return tt;
} 

//=========================================================
int Ritual::getActivationCost() const { return activationCost; }

//=========================================================
Ritual::Ritual(int cost, int activationCost, int charges, Player& owner, Player& opponent, const string& name, const string& description, TriggerType tt) 
    : Card {owner, opponent, name, cost}, activationCost {activationCost}, charges{charges}, tt{tt}, description{description} {
    trigger = std::make_unique<Trigger> (this);
}

const string& Ritual::get_description() const {
    return description;
}

//=========================================================
void Ritual::detachTrigger() {
    trigger->selfDetach();
}

// the subclasses have the responsibility of setting up the trigger for the correct trigger topic 

