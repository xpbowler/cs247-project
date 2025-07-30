#pragma once 

#include "spell.h"
#include <helper.h>

class Blizzard : public Spell {

public: 
    Blizzard(Player& owner, Player& opponent);

    bool action(std::variant<Minion*, Ritual*> card) override;

};
