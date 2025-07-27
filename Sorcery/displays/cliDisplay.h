#pragma once

#include "display.h"
#include "../player.h"

#include <vector>
#include <memory>

class CliDisplay : public Display {
    Player* player1;
    Player* player2;

    void showCard(const std::unique_ptr<Card>& card);

    public:
        CliDisplay(Player* player1, Player* player2);
        void inspectMinion(bool isPlayer1Turn, int minion) override;
        void showHand(bool isPlayer1Turn) override;
        void showBoard() override;
};