#pragma once 

#include "spell.h"

class Recharge : public Spell {

public: 
    Recharge();

    void action() override;
};

