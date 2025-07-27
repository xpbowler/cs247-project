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

    // responsibility on player to check if enough magic
    int getActivationCost() const;
    const std::string& getDescription() const;

protected: 
    const int activationCost;
    const std::string description;
    virtual void useSkill() = 0;

    virtual ~ActivatedMinion() {}

};
