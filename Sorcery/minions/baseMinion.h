#pragma once 

#include "minion.h"

/*
The purpose of this class is for clearer display of hierarchy, 
with the Air Elemental and Earth Elemental as the subclasses 
*/

class BaseMinion : public Minion {

public: 
    BaseMinion(Player& owner, Player& opponent) : Minion{owner, opponent} {}

protected: 

    virtual void useSkill() = 0;

    virtual ~BaseMinion() {}
};

  
