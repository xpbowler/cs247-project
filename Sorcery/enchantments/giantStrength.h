#ifndef __GIANT_STRENGTH_H__
#define __GIANT_STRENGTH_H__

#include "enchantmentDecorator.h"

class GiantStrength : public EnchantmentDecorator {

    public: 

    void apply(Minion& minion) override;
};

#endif 
