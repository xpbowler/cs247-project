#pragma once 

#include "enchantment.h"
#include <memory>

class EnchantmentDecorator : public Enchantment {

public: 
    EnchantmentDecorator (std::string name, Player& owner, Player& opponent, EnchantmentTiming et);

    Enchantment* getNext();

    // DANGEROUS: should be only called by Minion::removeTopEnchantment and Minion::removeAllEnchantment
    Enchantment* stealNext();
    void setNext(Enchantment* nextEnchantment);

    protected:
    std::unique_ptr<Enchantment> next;

    virtual ~EnchantmentDecorator() {}

};

  
