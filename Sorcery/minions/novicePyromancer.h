#pragma once 

#include "activatedMinion.h"

class NovicePyromancer : public ActivatedMinion {

public: 
    NovicePyromancer(Player& owner, Player& opponent);

    UseSkillStatus useSkill(bool isTesting) override;

    UseSkillStatus useSkill(bool isTesting, Minion* minion);

};

  
