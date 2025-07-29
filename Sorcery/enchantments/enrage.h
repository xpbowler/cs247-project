#pragma once 

#include "enchantmentDecorator.h"
#include "helper.h"

class Enrage : public EnchantmentDecorator {

public: 
    Enrage (Player& owner, Player& opponent);

    void apply(Minion& minion, EnchantmentTiming et) override;
};

  
