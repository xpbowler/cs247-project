#pragma once 

#include "minion.h"
#include <helper.h>
#include <memory>

class Trigger;
class Notification;

// abstract base class for minions with triggered abilities 
class TriggeredMinion : public Minion {

public: 

    virtual void useSkill(const Notification& notification) = 0;
    const TriggerType getTriggerType() const;
    Trigger& getTrigger();
    const TriggerType tt;
    const std::string& getDescription() const;
    void disableAbility();
    void detachTrigger();

protected: 

    TriggeredMinion(int attack, 
                    int defence, 
                    Player& owner, 
                    Player& opponent,
                    std::string name,
                    std::string description,
                    TriggerType tt, 
                    int cost,
                    MinionType minionType);

    // subclasses have responsibility to create trigger and attach to trigger topic
    std::unique_ptr<Trigger> trigger;
    std::string description;

    bool canUseAbility;

    virtual ~TriggeredMinion() {}

}; 

  
