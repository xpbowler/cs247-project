#pragma once 

#include "../card.h"
#include "../util.h"
#include <memory>
#include <vector>
#include <optional>

class EnchantmentDecorator;
class Enchantment;

class Minion : public Card {

public: 
    int getDefence();
    int getAttack();
    int getActions();
    const std::vector<Enchantment*> getEnchantments();
    void addEnchantment(std::unique_ptr<EnchantmentDecorator> enchantment);
    bool removeTopEnchantment();
    void removeAllEnchantments(std::optional<EnchantmentTiming> et);
    void applyEnchantment(EnchantmentTiming et);
    void setAttack(int attack);
    void setDefence(int defence);
    void heal(int hp);
    void takeDamage(int dmg);
    void setActions(int action);
    // attack minion and player returns false if not enough action points 
    bool attackMinion(Minion* minion, std::optional<int> dmg);
    bool attackPlayer(std::optional<int> dmg);
    void gainStats(int attack, int defence);
    void summonMinion(MinionType minionType, int amount);

// no need to put useSkill here, it is already in the intermediate subclasses

protected: 
    Minion(Player& owner, Player& opponent, int attack, int defence, MinionType mt, std::string name);

    virtual ~Minion() = 0;

    virtual void dies();

    int attack;
    int defence;
    int actions;
    MinionType minionType;
    std::unique_ptr<Enchantment> enchantment;
    std::string name;
    
    
};

  

