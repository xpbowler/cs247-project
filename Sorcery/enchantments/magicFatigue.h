#ifndef __MAGIC_FATIGUE_H__
#define __MAGIC_FATIGUE_H__

#include "enchantmentDecorator.h"

class MagicFatigue : public EnchantmentDecorator {

    public: 

    void apply(Minion& minion) override;
};

#endif 
