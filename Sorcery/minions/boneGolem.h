#pragma once 

#include "triggeredMinion.h"

class BoneGolem : public TriggeredMinion {

public: 
    BoneGolem();
    
    void useSkill(Notification notification) override;

};

  
