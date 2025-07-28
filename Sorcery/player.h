#pragma once

#include <vector>
#include <memory>
#include <variant>

#include "triggers/trigger.h"
#include "card.h"
#include "minions/minion.h"
#include "util.h"
#include "rituals/ritual.h"

class Game;

class Player {
    std::string name;
    int life;
    int magic;
    std::vector<std::unique_ptr<Card>> deck;
    std::vector<std::unique_ptr<Card>> hand;
    std::vector<std::unique_ptr<Card>> board;
    std::vector<std::unique_ptr<Card>> graveyard;
    std::unique_ptr<Ritual> ritual;
    const Player* otherPlayer;
    const Game& game;

    std::vector<std::unique_ptr<Card>>& areaToVec (Area area);


    public:
        Player(std::string& name, Game* game);
        // draw command draws a card, similar to the effect if the player just started their turn
        void drawCard();
        void playCard(Card* card);

        // discard the i'th card in the player's hand
        // the card does not go to the graveyard, trigger leave play effects or anything else
        void discardCard(int i);
        void notifyGame(TriggerType triggerType, Notification notification);
        bool moveCard(Card* card, Area src, Area dst);
        bool modifyLife(int life);
        const std::vector<std::unique_ptr<Card>>& getHand() const;
        const std::vector<std::unique_ptr<Card>>& getDeck() const;
        const std::vector<std::unique_ptr<Card>>& getBoard() const;
        Card* getGraveyardTop() const;
        Ritual* getRitual() const;
        const std::string& getName() const;
        void declareStart();
        void declareEnd();


        int getLife() const;
        int getMagic() const;
        void setMagic(int magic);
        const std::vector<std::unique_ptr<Card>>& getGraveyard() const;
        void setOtherPlayer(Player* player);
        bool isPlayer1() const;

        // summon minions of minionType, for amount, until it's full
        void summonMinion(MinionType minionType, int amount);


        // initialize the deck from a file
        void initializeDeck(const std::string& deck);

        // Shuffle the deck using std::shuffle and a random engine
        void shuffleDeck();

        // pass the trigger to the correct trigger topic
        void attachTrigger(TriggerType tt, Trigger* trigger);
        
};