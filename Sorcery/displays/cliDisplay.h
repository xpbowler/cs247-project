#include "display.h"
#include "player.h"

#include <vector>
#include <memory>

class CliDisplay : public Display {
    Player* 

    public:
        CliDisplay();
        void inspectMinion(bool isPlayer1Turn, int minion) override;
        void showHand(bool isPlayer1Turn) override;
        void showBoard() override;
};