#include "trigger.h"
#include "notification.h"
#include <triggeredMinion.h>
#include <ritual.h>
#include <helper.h>
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
        throw std::runtime_error("Trigger not found while detaching.");
        return;
    }
    observers.erase(foundTrigger);
}

//=========================================================
Trigger::Trigger(ownerPtr owner) : owner{owner} {}

//=========================================================
Trigger::~Trigger() {
    
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

//=========================================================
const std::string& Trigger::get_description() const {
    return description;
}

//=========================================================
void Trigger::selfDetach() {
    triggerTopic->detachTrigger(this);
    triggerTopic = nullptr;
}