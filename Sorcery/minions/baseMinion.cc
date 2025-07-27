#include "baseMinion.h"

//=========================================================
BaseMinion::BaseMinion(int attack,
                       int defence,
                       Player &owner,
                       Player &opponent,
                       std::string name,
                       MinionType minionType) : Minion{owner, opponent, attack, defence, minionType, name}
{
}
