#pragma once

#include <string>
#include <iostream>
#include <variant>
#include <card.h>
#include <minion.h>
#include <ritual.h>
#include <player.h>
class Player;

class Spell : public Card {

public: 
    const std::string& get_description() const;

    virtual void action(std::variant<Minion*, Ritual*> card) = 0;

    virtual ~Spell() {}

protected: 
    
    Spell(std::string description, Player& owner, Player& opponent, const std::string& name, int cost);

    std::string description;
};