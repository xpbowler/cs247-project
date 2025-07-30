#include "triggeredMinion.h"
#include <trigger.h>

//=========================================================
TriggeredMinion::TriggeredMinion(int attack,
                                 int defence,
                                 Player &owner,
                                 Player &opponent,
                                 std::string name,
                                 std::string description,
                                 int cost,
                                 MinionType minionType)
    : Minion{owner, opponent, attack, defence, minionType, name, cost}, description{std::move(description)}, canUseAbility {true}
{
    
}

//=========================================================
const Trigger& TriggeredMinion::getTrigger() {
    return *trigger;
}

//=========================================================
const std::string& TriggeredMinion::getDescription() const {
    return description;
}

//=========================================================
void TriggeredMinion::disableAbility() {
    canUseAbility = false;
}


//=========================================================
void TriggeredMinion::dies() {
    Minion::dies();
    // now detach the trigger
    trigger->selfDetach();
}