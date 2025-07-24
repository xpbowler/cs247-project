#pragma once 

#include "enchantment.h"

class BaseEnchantment : public Enchantment {

public: 
    void apply(Minion& minion) override;

};
