#pragma once 

#include "triggeredMinion.h"

class FireElemental : public TriggeredMinion {

public: 
    FireElemental(Player& owner, Player& opponent);

    void useSkill(Notification notification) override;

};
