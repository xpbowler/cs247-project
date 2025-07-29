#pragma once 

#include "enchantment.h"
#include <memory>

class EnchantmentDecorator : public Enchantment {

public: 
    EnchantmentDecorator (std::string description, Player& owner, Player& opponent, EnchantmentTiming et, std::string name, int cost);

    Enchantment* getNext();

    // DANGEROUS: should be only called by Minion::removeTopEnchantment and Minion::removeAllEnchantment
    Enchantment* stealNext();
    void setNext(Enchantment* nextEnchantment);

    virtual ~EnchantmentDecorator() {}

protected:
    std::unique_ptr<Enchantment> next;

    

};

  
