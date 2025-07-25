#pragma once 

#include "triggeredMinion.h"

class FireElemental : public TriggeredMinion {

public: 
    FireElemental();

    void useSkill(Notification notification) override;

};
