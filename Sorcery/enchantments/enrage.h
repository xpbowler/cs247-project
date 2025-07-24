#pragma once 

#include "enchantmentDecorator.h"

class Enrage : public EnchantmentDecorator {

    public: 

    void apply(Minion& minion) override;
};

  
