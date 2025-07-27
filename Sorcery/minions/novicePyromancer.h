#pragma once 

#include "activatedMinion.h"

class NovicePyromancer : public ActivatedMinion {

public: 
    NovicePyromancer(Player& owner, Player& opponent);

    UseSkillStatus useSkill() override;

    UseSkillStatus useSkill(Minion* minion);

};

  
