#ifndef __CARD_H__
#define __CARD_H__

#include <string>

class Player;

class Card {
protected: 
    Card(Player& owner, Player& opponent) : owner{owner}, opponent{opponent} {}

    Player& owner;
    Player& opponent;
    std::string name;
    int cost;

    virtual ~Card() = 0;

};

#endif 