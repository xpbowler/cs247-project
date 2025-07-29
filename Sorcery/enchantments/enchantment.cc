#include "enchantment.h"
#include <helper.h>

//=========================================================
Enchantment::Enchantment (const std::string description, Player& owner, Player& opponent, EnchantmentTiming et, std::string name, int cost) 
    : Card {owner, opponent, name, cost}, description {std::move(description)}, timing {et} {}

//=========================================================
const std::string& Enchantment::getDescription() const {
    return description;
}

//=========================================================
const EnchantmentTiming Enchantment::getTiming() const { 
    return timing;
}