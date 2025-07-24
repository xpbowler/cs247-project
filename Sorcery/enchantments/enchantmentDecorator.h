#pragma once 

#include "enchantment.h"
#include <memory>

class EnchantmentDecorator : public Enchantment {

    protected:
    std::unique_ptr<Enchantment> next;

    virtual ~EnchantmentDecorator() {}

};

  
