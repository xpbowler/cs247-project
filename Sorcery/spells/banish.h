#pragma once 

#include "spell.h"
#include <helper.h>

class Banish : public Spell {

public: 
    Banish(Player& owner, Player& opponent);
    
    void action(std::variant<Minion*, Ritual*> card) override;

};