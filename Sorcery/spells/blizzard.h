#pragma once 

#include "spell.h"
#include "../util.h"

class Blizzard : public Spell {

public: 
    Blizzard(Player& owner, Player& opponent);

    void action(std::variant<Minion*, Ritual*> card) override;

};