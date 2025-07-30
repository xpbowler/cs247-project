#pragma once

#include <memory>
#include <unordered_map>

#include "player.h"
#include <trigger.h>
#include <cliDisplay.h>

class Game {
    bool isPlayer1Turn;
    bool isTesting;
    bool bonusFeatures;
    mutable std::optional<bool> player1Wins;
    std::unordered_map<TriggerType, std::unique_ptr<TriggerTopic>> triggerTopics;
    std::unique_ptr<Display> display;
    
    public:
        std::unique_ptr<Player> player1, player2;

        Game(const std::string& deck1, const std::string& deck2, const std::string& initFile, bool isTesting, bool bonusFeatures);

        void notifyTopic(TriggerType triggerType, const Notification& notification) const;
        void attachTrigger(TriggerType tt, Trigger* trigger) const;
        TriggerTopic* getTriggerTopic(TriggerType triggerType) const;

        bool isBonusFeatures() const { return bonusFeatures; }
        
        void play();

        void declareWin(bool isPlayer1) const;

        const Player& getCurrentPlayer() const;
        
        // execute a command
        void executeCommand(const std::string& command);

};