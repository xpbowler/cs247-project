#pragma once 

#include "spell.h"
#include <helper.h>

class Disenchant : public Spell {

public: 
    Disenchant(Player& owner, Player& opponent);

    bool action(std::variant<Minion*, Ritual*> card) override;
};

