#pragma once 

#include "minion.h"
#include <util.h>
#include <memory>

class Trigger;
class TriggerType;
class Notification;

// abstract base class for minions with triggered abilities 
class TriggeredMinion : public Minion {

public: 

    virtual void useSkill(Notification notification) = 0;

protected: 

    TriggeredMinion(Player& owner, Player& opponent);

    std::unique_ptr<Trigger> trigger;

    void notifyGame(TriggerType tt);

    

    virtual ~TriggeredMinion() {}

}; 

  
