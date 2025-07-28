#pragma once 

#include "enchantmentDecorator.h"


class Silence : public EnchantmentDecorator {

public:
    Silence(Player& owner, Player& opponent);

    void apply(Minion& minion, EnchantmentTiming et) override;
};

  
