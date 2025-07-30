#include "spell.h"

//=========================================================
Spell::Spell(std::string description, Player& owner, Player& opponent, const std::string& name, int cost)
    : Card{owner, opponent, name, cost}, description{std::move(description)} {}

//=========================================================
const std::string& Spell::get_description() const {
    return description;
}
