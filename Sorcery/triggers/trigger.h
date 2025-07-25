#pragma once

#include <vector>
#include <variant>

class TriggeredMinion;
class Ritual;
class Trigger;
class Notification;

class TriggerTopic {
    std::vector<Trigger*> observers;
    public:
        TriggerTopic();
        void notifyTriggers(Notification notification);
        void attachTrigger(Trigger* trigger);
        void detachTrigger(Trigger* trigger);
};

class Trigger {
    using ownerPtr = std::variant<TriggeredMinion*, Ritual*>;
    TriggerTopic* triggerTopic {nullptr};
    ownerPtr owner;
    public:
        Trigger(ownerPtr owner);
        void notifyOwner(Notification notification);
        ~Trigger();
};
