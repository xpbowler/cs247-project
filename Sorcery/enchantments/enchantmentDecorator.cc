#include "enchantmentDecorator.h"
#include <helper.h>

//=========================================================
EnchantmentDecorator::EnchantmentDecorator(std::string description, 
                                           Player& owner, 
                                           Player& opponent, 
                                           EnchantmentTiming et, 
                                           std::string name, 
                                           int cost)
    : Enchantment {description, owner, opponent, et, name, cost} {}

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

