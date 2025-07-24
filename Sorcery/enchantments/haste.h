#ifndef __HASTE_H__
#define __HASTE_H__

#include "enchantmentDecorator.h"

class Haste : public EnchantmentDecorator {
    
    public: 
    void apply(Minion& minion) override;

};


#endif 

