#pragma once

class Display {
    public:
        virtual void inspectMinion(bool isPlayer1Turn, int minion) = 0;
        virtual void showHand(bool isPlayer1Turn) = 0;
        virtual void showBoard() = 0;
};