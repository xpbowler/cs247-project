#pragma once 

#include "../card.h"

class Minion;

class Enchantment : public Card {

public:
    Enchantment(const std::string& description);
    const std::string& get_description() const;
    virtual ~Enchantment() {}
    

protected: 
    virtual void apply(Minion& minion) = 0;
};

  
