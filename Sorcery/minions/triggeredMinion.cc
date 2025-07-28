#include "triggeredMinion.h"
#include <trigger.h>

//=========================================================
TriggeredMinion::TriggeredMinion(int attack,
                                 int defence,
                                 Player &owner,
                                 Player &opponent,
                                 std::string name,
                                 MinionType minionType)
    : Minion{owner, opponent, attack, defence, minionType, name}, canUseAbility {true}
{
    
}

//=========================================================
const Trigger& TriggeredMinion::getTrigger() {
    return *trigger;
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