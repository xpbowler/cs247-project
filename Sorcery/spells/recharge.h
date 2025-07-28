#pragma once 

#include "spell.h"
#include "../util.h"

#include <variant>

class Recharge : public Spell {

public: 
    Recharge(Player& owner, Player& opponent);

    void action(std::variant<Minion*, Ritual*> card) override;
};

