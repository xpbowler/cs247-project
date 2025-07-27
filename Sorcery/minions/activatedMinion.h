#pragma once

#include "minion.h"

// abstract base class for minions with activated abilities 
class ActivatedMinion : public Minion {

public: 
    ActivatedMinion(int activationCost, Player& owner, Player& opponent);

protected: 
    const int activationCost;

    virtual void useSkill() = 0;

    virtual ~ActivatedMinion() {}

};
