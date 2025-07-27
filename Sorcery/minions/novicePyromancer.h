#pragma once 

#include "activatedMinion.h"

class NovicePyromancer : public ActivatedMinion {

public: 
    NovicePyromancer(Player& owner, Player& opponent);

    void useSkill() override;

    void useSkill(Minion* minion);

};

  
