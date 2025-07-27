#pragma once 

#include "triggeredMinion.h"

class PotionSeller : public TriggeredMinion {
    
public: 
    PotionSeller(Player& owner, Player& opponent);

    void useSkill(Notification notification) override;
};
