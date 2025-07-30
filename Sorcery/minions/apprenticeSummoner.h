#pragma once 

#include "activatedMinion.h"

class ApprenticeSummoner : public ActivatedMinion {

public: 
    ApprenticeSummoner(Player& owner, Player& opponent);

    UseSkillStatus useSkill(bool isTesting) override;

};

  
