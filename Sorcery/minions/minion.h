#pragma once 

#include "../card.h"
#include "../util.h"
#include <memory>
#include <vector>

class Enchantment;

class Minion : public Card {

public: 
    int getDefence();
    int getAttack();
    int getActions();
    const std::vector<Enchantment*> getEnchantments();
    void setAttack(int attack);
    void heal(int hp);
    void takeDamage(int dmg);
    void setAction(int action);
    void attackMinion(Minion* minion, int dmg);
    void attackPlayer(int dmg);
    void gainStats(int attack, int defence);
    void summonMinion(MinionType minionType, int amount);

// no need to put useSkill here, it is already in the intermediate subclasses

protected: 
    Minion(Player& owner, Player& opponent, int attack, int defence, MinionType mt, std::string name);

    virtual ~Minion() = 0;

    int attack;
    int defence;
    int actions;
    MinionType minionType;
    std::unique_ptr<Minion> enchantment;
    std::string name;

private:
    void dies();
    
};

  

