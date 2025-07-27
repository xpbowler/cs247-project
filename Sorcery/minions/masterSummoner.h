#pragma once 

#include "activatedMinion.h"

class MasterSummoner : public ActivatedMinion {

public: 
    MasterSummoner(Player& owner, Player& opponent);

    void useSkill() override;

};


  
