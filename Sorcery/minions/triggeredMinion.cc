#include "triggeredMinion.h"

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
void TriggeredMinion::notifyGame(TriggerType tt)
{
    // TODO
}

//=========================================================
void TriggeredMinion::disableAbility() {
    canUseAbility = false;
}
