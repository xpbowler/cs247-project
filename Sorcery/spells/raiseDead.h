#pragma once 

#include "spell.h" 
#include <helper.h>

class RaiseDead : public Spell {

public: 

    RaiseDead(Player& owner, Player& opponent);

    bool action(std::variant<Minion*, Ritual*> card) override;

};

