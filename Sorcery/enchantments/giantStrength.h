#pragma once 

#include "enchantmentDecorator.h"

class GiantStrength : public EnchantmentDecorator {

public: 

    GiantStrength(Player& owner, Player& opponent);

    void apply(Minion& minion, EnchantmentTiming et) override;
};

  
