#pragma once 

#include "ritual.h"

class Standstill : public Ritual {

public: 
    Standstill(Player& owner, Player& opponent);

    void execute(const Notification& notification) override;

};
