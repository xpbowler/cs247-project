#pragma once 

#include <string>

class Player;

class Card {
protected: 
    Card(Player& owner, Player& opponent, const std::string& name, int cost) : owner{owner}, opponent{opponent}, name{name}, cost{cost} {}

    Player& owner;
    Player& opponent;
    std::string name;
    int cost;
public:
    const std::string& get_name() const;
    const int get_cost() const;
    Player& getOwner();
    Player& getOpponent();
    virtual ~Card() = 0;
    
};
