#pragma once

#include "display.h"
#include "../player.h"
#include "../asciiart/ascii_graphics.h"

#include <vector>
#include <memory>

class CliDisplay : public Display {
    const Player& p1;
    const Player& p2;


    public:
        CliDisplay(const Player& p1, const Player& p2);
        void inspectMinion(bool isPlayer1Turn, int minion) override;
        void showHand(bool isPlayer1Turn) override;
        void showBoard() override;
};