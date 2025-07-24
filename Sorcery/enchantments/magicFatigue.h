#pragma once 

#include "enchantmentDecorator.h"

class MagicFatigue : public EnchantmentDecorator {

public: 

    void apply(Minion& minion) override;
};

  
