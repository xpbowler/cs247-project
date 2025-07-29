#pragma once

#include "spell.h"
#include <helper.h>

class Unsummon : public Spell {

public:
    Unsummon(Player& owner, Player& opponent);

    void action(std::variant<Minion*, Ritual*> card) override;

};

