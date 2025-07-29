#include "spell.h"

//=========================================================
Spell::Spell(std::string description, Player& owner, Player& opponent, const std::string& name, int cost): description{description}, Card{owner, opponent, name, cost} {}

//=========================================================
const std::string& Spell::get_description() const {
    return description;
}