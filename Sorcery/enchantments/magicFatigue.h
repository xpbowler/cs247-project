#pragma once 

#include "enchantmentDecorator.h"

class MagicFatigue : public EnchantmentDecorator {

public: 
    MagicFatigue(Player& owner, Player& opponent);

    void apply(Minion& minion, EnchantmentTiming et) override;
};

  
