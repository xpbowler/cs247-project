#ifndef __SILENCE_H__
#define __SILENCE_H__

#include "enchantmentDecorator.h"

class Silence : public EnchantmentDecorator {

    public: 

    void apply(Minion& minion) override;
};

#endif 
