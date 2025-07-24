#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__

#include "../card.h"

class Minion;

class Enchantment : public Card {
protected: 

    virtual void apply(Minion& minion) = 0;

    virtual ~Enchantment() {}

};

#endif 
