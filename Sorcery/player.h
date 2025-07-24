#include <vector>
#include <memory>

#include "trigger.h"
#include "card.h"
#include "minion.h"
#include "util.h"


class Player {
    std::string name;
    int life;
    int magic;
    std::vector<std::unique_ptr<Card>> deck;
    std::vector<std::unique_ptr<Card>> hand;
    std::vector<std::unique_ptr<Card>> board;
    std::vector<std::unique_ptr<Card>> graveyard;
    std::unique_ptr<Ritual> ritual
    Player* otherPlayer;

    public:
        Player(const std::string& deck);
        bool drawCard();
        bool playCard(Card* card);
        void notifyGame(TriggerType triggerType);
        bool moveCard(Minion* minion, Area src, Area dst);
        bool modifyLife(int life);
        const std::vector<std::unique_ptr<Card>>& getHand();
        const std::vector<std::unique_ptr<Card>>& getDeck();
        const std::vector<std::unique_ptr<Card>>& getBoard();
        void addTrigger(Trigger* trigger);
        void removeTrigger(Trigger* trigger);
        
};