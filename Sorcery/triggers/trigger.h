#pragma once

#include <vector>
#include <variant>
#include <string>

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
    std::string description;
    public:
        Trigger(ownerPtr owner);
        void notifyOwner(Notification notification);
        const std::string& get_description() const;
        ~Trigger();
};
