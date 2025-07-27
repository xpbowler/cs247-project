#pragma once 

#include "spell.h"
#include "../util.h"

class Disenchant : public Spell {

public: 
    Disenchant(Player& owner, Player& opponent);

    void action(std::variant<Minion*, Ritual*> card) override;
};

