#pragma once 

#include "ritual.h"

class DarkRitual : public Ritual {

public: 
    DarkRitual(Player& owner, Player& opponent);

    void execute(Notification notification) override;

};

