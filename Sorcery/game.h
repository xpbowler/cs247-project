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
        void declareWin(bool isPlayer1) const;
        const Player& getCurrentPlayer() const;
        std::optional<bool> isPlayer1Wins() const;
        
        // API that controller interacts with
        void endTurn(std::stringstream& ss);
        void discardCard(std::stringstream& ss);
        void drawCard(std::stringstream& ss);
        void attack(std::stringstream& ss);
        void playCard(std::stringstream& ss);
        void useCard(std::stringstream& ss);
        void inspectMinion(std::stringstream& ss);
        void displayHand(std::stringstream& ss);
        void displayBoard(std::stringstream& ss);

};
