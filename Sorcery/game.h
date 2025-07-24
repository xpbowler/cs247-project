#include <memory>
#include <unordered_map>

#include "player.h"
#include "trigger.h"

class Game {
    std::unordered_map<TriggerType, std::unique_ptr<TriggerTopic>> triggerTopics;
    
    public:
        Game(Player player1, Player player2);

        std::unique_ptr<Player> player1, player2;
        void notifyTopic(TriggerType triggerType);
        void addTrigger(TriggerType triggerType, Trigger* trigger);
        void removeTrigger(TriggerType triggerType, Trigger* trigger);

};