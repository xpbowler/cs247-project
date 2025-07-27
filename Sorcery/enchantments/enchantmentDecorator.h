#pragma once 

#include "enchantment.h"
#include <memory>

class EnchantmentDecorator : public Enchantment {

public: 
    EnchantmentDecorator ();

    Enchantment* getNext();

    // DANGEROUS: should be only called by Minion::removeTopEnchantment
    Enchantment* stealNext();
    void setNext(Enchantment* nextEnchantment);

    protected:
    std::unique_ptr<Enchantment> next;

    virtual ~EnchantmentDecorator() {}

};

  
