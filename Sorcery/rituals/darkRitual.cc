#include "darkRitual.h"
#include "notification.h"
#include "player.h"
#include <iostream>

//=========================================================
DarkRitual::DarkRitual(Player& owner, Player& opponent) : Ritual {DARK_RITUAL_COST, 
                                                                  DARK_RITUAL_ACTIVATION_COST,
                                                                  DARK_RITUAL_CHARGES, 
                                                                  owner, opponent, DARK_RITUAL, DARK_RITUAL_DESC, 
                                                                  owner.isPlayer1() ? StartTurnPlayer1 : StartTurnPlayer2} {
    
}

//=========================================================
void DarkRitual::execute(const Notification& notification) {
    // Check if real notification type
    auto realNoti = dynamic_cast<const TurnChangeNotification*>(&notification);
    if (!realNoti) {
        return;
    }
    // Check if player starting turn is the owner of ritual
    if (&owner != realNoti->player) {
        return;
    }
    // Check if start of turn
    if (!realNoti->isStart) {
        return;
    }
    // Check if enough charges
    if (charges < activationCost) {
        return;
    }
    // Execute ritual
    charges -= activationCost;
    std::cout << "dark ritual here" << std::endl;
    owner.setMagic(owner.getMagic() + 1);
}
