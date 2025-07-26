#include "trigger.h"
#include "notification.h"
#include <triggeredMinion.h>
#include <ritual.h>
#include "util.h"
#include <iostream>

#include <algorithm>

//=========================================================
TriggerTopic::TriggerTopic() {}


//=========================================================
void TriggerTopic::notifyTriggers(Notification notification) {
    for (auto& observer : observers) {
        observer->notifyOwner(notification);
    }
}

//=========================================================
void TriggerTopic::attachTrigger(Trigger* trigger) {
    observers.push_back(trigger);
}

//=========================================================
void TriggerTopic::detachTrigger(Trigger* trigger) {
    const auto foundTrigger = find(observers.begin(), observers.end(), trigger);
    if (foundTrigger == observers.end()) {
        // TODO: improve this error reporting 
        std::cerr << "Trigger not found" << std::endl;
        return;
    }
    observers.erase(foundTrigger);
}

//=========================================================
Trigger::Trigger(ownerPtr owner) : owner{owner} {}

//=========================================================
Trigger::~Trigger() {
    // TODO: we probably have to go through the "minion leaves play" trigger, if it is a triggered minion leaving play, before destroying this trigger, right?
    // we need to detach 
    triggerTopic->detachTrigger(this);
    // TODO: is there anything im missing?
}

//=========================================================
void Trigger::notifyOwner(Notification notification) {
    if (owner.index() == 0) {
        auto minion = std::get<0> (owner);
        minion->useSkill(notification);
    }
    else {
        auto ritual = std::get<1> (owner);
        ritual->execute(notification);
    }
}
