#include "triggeredMinion.h"
#include <trigger.h>

//=========================================================
TriggeredMinion::TriggeredMinion(int attack,
                                 int defence,
                                 Player &owner,
                                 Player &opponent,
                                 std::string name,
                                 std::string description,
                                 TriggerType tt, 
                                 int cost,
                                 MinionType minionType)
    : Minion{owner, opponent, attack, defence, minionType, name, cost}, tt{tt}, description{std::move(description)}, canUseAbility {true}
{
    
}

//=========================================================
const TriggerType TriggeredMinion::getTriggerType() const {
    return tt;
}

//=========================================================
Trigger& TriggeredMinion::getTrigger() {
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
void TriggeredMinion::detachTrigger() {
    trigger->selfDetach();
}


