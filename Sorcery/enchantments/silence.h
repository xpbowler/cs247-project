#pragma once 

#include "enchantmentDecorator.h"

class Silence : public EnchantmentDecorator {

    public: 

    void apply(Minion& minion) override;
};

  
