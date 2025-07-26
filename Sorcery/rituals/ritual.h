#pragma once 

#include <memory>

class Trigger;
class Notification;

class Ritual {
    protected: 
        Ritual(int cost, int charges);

        virtual void execute(Notification notification) = 0;

        virtual ~Ritual() {};

        // member fields
        const int activationCost;
        int charges;
        std::unique_ptr<Trigger> trigger;

    public: 
        int getCharges() const;
        void setCharges(int charges);
};