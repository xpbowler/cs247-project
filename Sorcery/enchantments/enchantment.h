#pragma once 

#include "../card.h"

class Minion;

class Enchantment : public Card {

public: 
    virtual ~Enchantment() {}

protected: 

    virtual void apply(Minion& minion) = 0;

    

};

  
