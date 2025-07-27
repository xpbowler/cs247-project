#include "spell.h"

//=========================================================
Spell::Spell(std::string description, Player& owner, Player& opponent): description{description}, Card{owner, opponent} {}