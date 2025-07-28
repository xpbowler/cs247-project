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
    void setActivationCost(int cost);
    const std::string& getDescription() const;
    void disableAbility();

protected: 
    int activationCost;
    const std::string description;
    bool canUseAbility;
    virtual UseSkillStatus useSkill() = 0;

    virtual ~ActivatedMinion() {}

};
