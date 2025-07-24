#pragma once 

#include "spell.h"

class Unsummon : public Spell {

public: 
    Unsummon();

    void action() override; 

};

