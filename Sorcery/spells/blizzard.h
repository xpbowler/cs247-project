#pragma once 

#include "spell.h"

class Blizzard : public Spell {

public: 
    Blizzard();

    void action() override;

};