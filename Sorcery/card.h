#pragma once 

#include <string>

class Player;

class Card {
protected: 
    Card(Player& owner, Player& opponent) : owner{owner}, opponent{opponent} {}

    Player& owner;
    Player& opponent;
    std::string name;
    int cost;
public:
    std::string& get_name() const;
    int get_cost() const;
    virtual ~Card() = 0;
    
};
