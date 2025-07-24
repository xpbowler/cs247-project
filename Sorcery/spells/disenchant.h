#pragma once 

#include "spell.h"

class Disenchant : public Spell {

public: 
    Disenchant();

    void action() override;
};

