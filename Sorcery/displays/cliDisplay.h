#include "display.h"

class CliDisplay : public Display {
    public:
        CliDisplay();
        void inspectMinion(bool isPlayer1Turn, int minion) override;
        void showHand(bool isPlayer1Turn) override;
        void showBoard() override;
};