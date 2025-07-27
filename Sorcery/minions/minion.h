#pragma once 

#include <card.h>
#include <memory>
#include <util.h>

class BaseEnchantment;

class Minion : public Card {

public: 
    int getDefence();
    int getAttack();
    int getActions();
    void setAttack(int attack);
    void heal(int hp);
    void takeDamage(int dmg);
    void setAction(int action);
    void attackMinion(Minion* minion);
    void attackPlayer(int dmg);
    void gainStats(int attack, int defence);
    void summonMinion(MinionType minionType, int amount);

// no need to put useSkill here, it is already in the intermediate subclasses

protected: 
    Minion(Player& owner, Player& opponent, int attack, int defence);

    virtual ~Minion() = 0;

    int attack;
    int defence;
    int actions;
    MinionType minionType;
    std::unique_ptr<BaseEnchantment> enchantment;
    std::string name;
    
};

  

