#pragma once

#include "minion.h"

// abstract base class for minions with activated abilities 
class ActivatedMinion : public Minion {

public: 
    ActivatedMinion(int activationCost, 
                    int attack, 
                    int defence, 
                    Player& owner,
                    Player& opponent, 
                    MinionType minionType,
                    std::string name);

protected: 
    const int activationCost;

    virtual void useSkill() = 0;

    virtual ~ActivatedMinion() {}

};
