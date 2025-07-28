#pragma once 

#include "enchantment.h"

class BaseEnchantment : public Enchantment {

public: 
    BaseEnchantment(Player& owner, Player& opponent);

    void apply(Minion& minion, 
               EnchantmentTiming et) override;

};
