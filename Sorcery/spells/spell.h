#pragma once

#include <string>
#include <iostream>

class Spell {

public: 
    void describe(std::ostream& out);

protected: 
    
    Spell(std::string description);

    std::string description;

    virtual void action() = 0;

    virtual ~Spell() {}
};