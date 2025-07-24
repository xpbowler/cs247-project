#pragma once 

#include "spell.h"

class Banish : public Spell {

public: 
    Banish();
    
    void action() override;

};