#pragma once 

#include "ritual.h"

class AuraOfPower : public Ritual {

public: 

    AuraOfPower(Player& owner, Player& opponent);

    void execute(const Notification& notification) override;

};
