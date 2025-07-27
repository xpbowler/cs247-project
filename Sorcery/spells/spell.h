#pragma once

#include <string>
#include <iostream>
#include "../card.h"

class Spell : Card {

public: 
    void describe(std::ostream& out);

protected: 
    
    Spell(std::string description);

    std::string description;

    virtual void action() = 0;

    virtual ~Spell() {}
};