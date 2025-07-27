#pragma once 

#include "minion.h"

/*
The purpose of this class is for clearer display of hierarchy, 
with the Air Elemental and Earth Elemental as the subclasses 
*/

class BaseMinion : public Minion {

public: 
    BaseMinion(int attack, 
               int defence, 
               Player& owner, 
               Player& opponent,
               std::string name, 
               MinionType minionType);

protected: 

    virtual ~BaseMinion() {}
};

  
