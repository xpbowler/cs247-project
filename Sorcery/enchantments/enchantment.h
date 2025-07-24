#pragma once 

#include "../card.h"

class Minion;

class Enchantment : public Card {
protected: 

    virtual void apply(Minion& minion) = 0;

    virtual ~Enchantment() {}

};

  
