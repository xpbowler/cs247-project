#pragma once 

#include <memory>
#include "../card.h"

class Trigger;
class Notification;

class Ritual : public Card {

public: 
    virtual void execute(Notification notification) = 0;
    int getCharges() const;
    void setCharges(int charges);

protected: 
    
    Ritual(int cost, int charges);

    virtual ~Ritual() {};

    // member fields
    const int activationCost;
    int charges;
    std::unique_ptr<Trigger> trigger;

    public: 
        int getCharges() const;
        void setCharges(int charges);
};