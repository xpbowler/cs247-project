#ifndef __ENRAGE_H__
#define __ENRAGE_H__

#include "enchantmentDecorator.h"

class Enrage : public EnchantmentDecorator {

    public: 

    void apply(Minion& minion) override;
};

#endif 
