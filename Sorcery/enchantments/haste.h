#pragma once 

#include "enchantmentDecorator.h"
#include "helper.h"

class Haste : public EnchantmentDecorator {
    
public: 
    Haste(Player& owner, Player& opponent);

    void apply(Minion& minion, EnchantmentTiming et) override;

};


  

