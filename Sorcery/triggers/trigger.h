#pragma once

#include <vector>

class Card;
class Trigger;

class TriggerTopic {
    std::vector<Trigger*> observers;
    public:
        TriggerTopic();
        void notifyTriggers();
        void attachTrigger(Trigger* trigger);
        void detachTrigger(Trigger* trigger);
};

class Trigger {
    TriggerTopic* triggerTopic;
    Card* owner;
    public:
        Trigger();
        void notifyOwner();
};