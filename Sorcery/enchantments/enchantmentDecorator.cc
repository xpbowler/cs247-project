#include "enchantmentDecorator.h"
#include <util.h>

//=========================================================
EnchantmentDecorator::EnchantmentDecorator(std::string name, 
                                           Player& owner, 
                                           Player& opponent, 
                                           EnchantmentTiming et)
    : Enchantment {name, owner, opponent, et} {}

//=========================================================
Enchantment* EnchantmentDecorator::getNext() {
    return next.get();
}

//=========================================================
Enchantment* EnchantmentDecorator::stealNext() {
    return next.release();
}

//=========================================================
void EnchantmentDecorator::setNext(Enchantment* nextEnchantment) {
    next.reset(nextEnchantment);
}

