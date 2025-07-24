#pragma once

#include <memory>
#include <unordered_map>

#include "player.h"
#include "triggers/trigger.h"

class Game {
    bool isPlayer1Turn;
    std::unordered_map<TriggerType, std::unique_ptr<TriggerTopic>> triggerTopics;
    
    public:
        std::unique_ptr<Player> player1, player2;

        Game(const std::string& deck1, const std::string& deck2, const std::string& initFile, bool isTesting);
        void notifyTopic(TriggerType triggerType);
        void addTrigger(TriggerType triggerType, Trigger* trigger);
        void removeTrigger(TriggerType triggerType, Trigger* trigger);
        void play();
        void executeCommand(const std::string& command);

};