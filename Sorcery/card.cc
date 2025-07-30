#include "card.h"

//=========================================================================
const std::string& Card::get_name() const {
    return name;
} 

//=========================================================================
const int Card::get_cost() const {
    return cost;
}

//=========================================================================
Player& Card::getOwner() {
    return owner;
}

Player& Card::getOpponent() {
    return opponent;
}

//=========================================================================
Card::~Card() {}
