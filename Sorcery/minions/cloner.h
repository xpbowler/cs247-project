#pragma once 

#include "activatedMinion.h"

class Cloner : public ActivatedMinion {

public:
    Cloner(Player& owner, Player& opponent);

    UseSkillStatus useSkill(bool isTesting) override;

    UseSkillStatus useSkill(bool isTesting, Minion* minion);

};

