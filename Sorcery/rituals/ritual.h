#pragma once 

#include <memory>

class Trigger;

class Ritual {

public: 

    int getCharges() const;
    void setCharges(int charges);

protected: 
    
    Ritual(int cost, int charges);

    virtual void execute() = 0;

    virtual ~Ritual() {};

    // member fields
    const int activationCost;
    int charges;
    std::unique_ptr<Trigger> trigger;

};