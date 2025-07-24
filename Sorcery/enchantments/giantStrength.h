#pragma once 

#include "enchantmentDecorator.h"

class GiantStrength : public EnchantmentDecorator {

    public: 

    void apply(Minion& minion) override;
};

  
