#pragma once 

#include <card.h>

class Minion : public Card {

public: 
    Minion(Player& owner, Player& opponent);

// TODO: implement rest of the public and protected fields for this
// no need to put useSkill here, it is already in the intermediate subclasses

protected: 

    virtual ~Minion() = 0;

};

  

