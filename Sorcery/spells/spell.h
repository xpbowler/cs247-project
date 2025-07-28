#pragma once

#include <string>
#include <iostream>
#include <variant>
#include "../card.h"
#include "../minions/minion.h"
#include "../rituals/ritual.h"
#include "../player.h"
class Player;

class Spell : public Card {

public: 
    const std::string& get_description() const;

    virtual void action(std::variant<Minion*, Ritual*> card) = 0;

    virtual ~Spell() {}

protected: 
    
    Spell(std::string description, Player& owner, Player& opponent);

    std::string description;
};