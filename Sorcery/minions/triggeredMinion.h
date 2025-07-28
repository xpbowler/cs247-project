#pragma once 

#include "minion.h"
#include "../util.h"
#include <memory>

class Trigger;
class Notification;

// abstract base class for minions with triggered abilities 
class TriggeredMinion : public Minion {

public: 

    virtual void useSkill(Notification notification) = 0;
    const Trigger& getTrigger();
    void disableAbility();
    void dies() override;

protected: 

    TriggeredMinion(int attack, 
                    int defence, 
                    Player& owner, 
                    Player& opponent,
                    std::string name, 
                    MinionType minionType);

    // subclasses have responsibility to create trigger and attach to trigger topic
    std::unique_ptr<Trigger> trigger;

    void notifyGame(TriggerType tt);
    bool canUseAbility;

    virtual ~TriggeredMinion() {}

}; 

  
