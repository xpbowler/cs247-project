#pragma once 

#include "spell.h"
#include "helper.h"

#include <variant>

class Recharge : public Spell {

public: 
    Recharge(Player& owner, Player& opponent);

    void action(std::variant<Minion*, Ritual*> card) override;
};

