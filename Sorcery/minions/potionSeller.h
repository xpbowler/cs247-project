#pragma once 

#include "triggeredMinion.h"

class PotionSeller : public TriggeredMinion {
    
public: 
    PotionSeller();

    void useSkill(Notification notification) override;
};
