#ifndef __BASE_ENCHANTMENT_H__
#define __BASE_ENCHANTMENT_H__

#include "enchantment.h"

class BaseEnchantment : public Enchantment {

public: 
    void apply(Minion& minion) override;

};

#endif 
