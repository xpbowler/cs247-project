#include "trigger.h"
#include "notification.h"
#include <triggeredMinion.h>
#include <ritual.h>
#include <helper.h>
#include <game.h>
#include <iostream>

#include <algorithm>

//=========================================================
TriggerTopic::TriggerTopic(Game& game) : game{game} {}

//=========================================================
void TriggerTopic::notifyTriggers(const Notification& notification) {
    // TODO: APNAP order?
    std::vector<Trigger*> observersCurrPlayer;
    std::vector<Trigger*> observersOtherPlayer;
    const Player& currPlayer = game.getCurrentPlayer();
    // look for minions
    for (const auto& observer : observers) {
        if (std::holds_alternative<TriggeredMinion*>(observer->getOwner())) {
            auto minion = std::get<TriggeredMinion*> (observer->getOwner());
            if (&minion->getOwner() == &currPlayer) {
                observersCurrPlayer.push_back(observer);
            }
            else {
                observersOtherPlayer.push_back(observer);
            }
        }
    }
    // look for current player's ritual
    for (const auto& observer : observers) {
        if (std::holds_alternative<Ritual*> (observer->getOwner())) {
            auto ritual = std::get<Ritual*> (observer->getOwner());
            if (&ritual->getOwner() == &currPlayer) {
                observersCurrPlayer.push_back(observer);
            }
            else {
                observersOtherPlayer.push_back(observer);
            }
        }
    }
    for (auto& observer : observersCurrPlayer) {
        std::cout << "notified currPlayer" << std::endl;
        observer->notifyOwner(notification);
    }
    for (auto& observer : observersOtherPlayer) {
        std::cout << "notified otherPlayer" << std::endl;
        observer->notifyOwner(notification);
    }
}

//=========================================================
void TriggerTopic::attachTrigger(Trigger* trigger) {
    std::cout << "attached something" << std::endl;
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
Trigger::ownerPtr Trigger::getOwner() const {
    return owner;
}

//=========================================================
void Trigger::notifyOwner(const Notification& notification) {
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
void Trigger::selfDetach() {
    triggerTopic->detachTrigger(this);
    triggerTopic = nullptr;
}