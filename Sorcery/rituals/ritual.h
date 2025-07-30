#pragma once 

#include <memory>
#include "../card.h"
#include "../triggers/trigger.h"
#include <helper.h>

class Trigger;
class Notification;

class Ritual : public Card {

public:
    virtual void execute(const Notification& notification) = 0;
    int getCharges() const;
    Trigger& getTrigger() const;
    const TriggerType getTriggerType() const;
    int getActivationCost() const;
    void setCharges(int charges);
    const std::string& get_description() const;
    void detachTrigger();
    virtual ~Ritual() {};

protected: 
    std::string description;
    Ritual(int cost, int activationCost, int charges, Player& owner, Player& opponent, const std::string& name, const std::string& description, TriggerType tt);

    // member fields
    const int activationCost;
    int charges;
    std::unique_ptr<Trigger> trigger;
    TriggerType tt;
};