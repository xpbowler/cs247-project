#pragma once 

#include "enchantmentDecorator.h"

class Haste : public EnchantmentDecorator {
    
    public: 
    void apply(Minion& minion) override;

};


  

