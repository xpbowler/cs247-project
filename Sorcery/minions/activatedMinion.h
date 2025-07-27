#pragma once

#include "minion.h"

// abstract base class for minions with activated abilities 
class ActivatedMinion : public Minion {

public: 
    ActivatedMinion(int activationCost, Player& owner, Player& opponent, const std::string& description);
    int getActivationCost() const;
    const std::string& getDescription() const;
protected: 
    const int activationCost;
    const std::string description;
    virtual void useSkill() = 0;

    virtual ~ActivatedMinion() {}

};
