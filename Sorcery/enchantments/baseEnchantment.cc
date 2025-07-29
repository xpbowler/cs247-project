#include "baseEnchantment.h"
#include <helper.h>

//===================================================================
BaseEnchantment::BaseEnchantment(Player& owner, Player& opponent) 
    : Enchantment {"Base Enchantment", owner, opponent, Never, "", 0} {}

//===================================================================
void BaseEnchantment::apply(Minion&, EnchantmentTiming) {
    // should do nothing
}
