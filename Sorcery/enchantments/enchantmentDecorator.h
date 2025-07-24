#ifndef __ENCHANTMENT_DECORATOR_H__
#define __ENCHANTMENT_DECORATOR_H__

#include "enchantment.h"
#include <memory>

class EnchantmentDecorator : public Enchantment {

    protected:
    std::unique_ptr<Enchantment> next;

    virtual ~EnchantmentDecorator() {}

};

#endif 
