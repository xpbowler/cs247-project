#pragma once 

#include "spell.h"
#include "../util.h"

class Recharge : public Spell {

public: 
    Recharge(Player& owner, Player& opponent);

    void action(variant<Minion*, Ritual*> card) override;
};

