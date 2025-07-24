#pragma once 

#include "minion.h"
#include "../util.h"
#include <memory>

class Trigger;

// abstract base class for minions with triggered abilities 
class TriggeredMinion : public Minion {

protected: 
    std::unique_ptr<Trigger> trigger;

    void notifyGame(TriggerType tt);

    virtual ~TriggeredMinion() {}

}; 

  
