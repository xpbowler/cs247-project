#pragma once 

#include <string>

class Player;

class Card {
public:
    virtual ~Card() = 0;

protected: 
    Card(Player& owner, Player& opponent) : owner{owner}, opponent{opponent} {}

    Player* owner;
    Player* opponent;
    std::string name;
    int cost;

    

};
