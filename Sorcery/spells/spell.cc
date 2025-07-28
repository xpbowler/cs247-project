#include "spell.h"

//=========================================================
Spell::Spell(std::string description, Player& owner, Player& opponent): description{description}, Card{owner, opponent} {}

//=========================================================
const std::string& Spell::get_description() const {
    return description;
}