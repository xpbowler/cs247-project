#include "enchantment.h"
#include <helper.h>

//=========================================================
Enchantment::Enchantment (const std::string description, Player& owner, Player& opponent, EnchantmentTiming et) 
    : Card {owner, opponent}, description {std::move(description)}, timing {et} {}

//=========================================================
const std::string& Enchantment::getDescription() const {
    return description;
}

//=========================================================
const EnchantmentTiming Enchantment::getTiming() const { 
    return timing;
}