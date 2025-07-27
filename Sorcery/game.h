#pragma once

#include <memory>
#include <unordered_map>

#include "player.h"
#include "triggers/trigger.h"
#include "displays/cliDisplay.h"

class Game {
    bool isPlayer1Turn;
    bool isTesting;
    std::unordered_map<TriggerType, std::unique_ptr<TriggerTopic>> triggerTopics;
    std::unique_ptr<Display> display;
    
    public:
        std::unique_ptr<Player> player1, player2;

        Game(const std::string& deck1, const std::string& deck2, const std::string& initFile, bool isTesting);

        void notifyTopic(TriggerType triggerType);
        void attachTrigger(TriggerType tt, Trigger* trigger);
        TriggerTopic* getTriggerTopic(TriggerType triggerType) const;
        
        void play();
        
        // execute a command
        void executeCommand(const std::string& command);

};