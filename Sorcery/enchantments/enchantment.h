#pragma once 

#include <card.h>
#include <helper.h>

class Minion;

class Enchantment : public Card {

public:
    Enchantment(const std::string description, Player& owner, Player& opponent, EnchantmentTiming et, std::string name, int cost);
    const std::string& getDescription() const;
    const EnchantmentTiming getTiming() const;
    virtual ~Enchantment() {}
    
    virtual void apply(Minion& minion, EnchantmentTiming et) = 0;

protected: 
    const std::string description;
    const EnchantmentTiming timing;
    
};

  
