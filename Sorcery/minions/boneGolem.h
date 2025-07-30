#pragma once 

#include "triggeredMinion.h"

class BoneGolem : public TriggeredMinion {

public: 
    BoneGolem(Player& owner, Player& opponent);
    
    void useSkill(const Notification& notification) override;

};

  
