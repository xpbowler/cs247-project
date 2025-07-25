#pragma once 

#include "minion.h"

/*
The purpose of this class is for clearer display of hierarchy, 
with the Air Elemental and Earth Elemental as the subclasses 
*/

class BaseMinion : public Minion {

protected: 

    virtual void useSkill() = 0;

    virtual ~BaseMinion() {}
};

  
