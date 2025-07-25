#pragma once

#include "minion.h"

// abstract base class for minions with activated abilities 
class ActivatedMinion : public Minion {
    ActivatedMinion(int activationCost);

protected: 
    const int activationCost;

    virtual void useSkill() = 0;

    virtual ~ActivatedMinion() {}

};
