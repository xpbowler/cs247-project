#include "darkRitual.h"
#include "notification.h"
#include "player.h"

//=========================================================
DarkRitual::DarkRitual(Player& owner, Player& opponent) : Ritual {DARK_RITUAL_COST, 
                                                                  DARK_RITUAL_ACTIVATION_COST,
                                                                  DARK_RITUAL_CHARGES, 
                                                                  owner, opponent, DARK_RITUAL, DARK_RITUAL_DESC} {
    owner.attachTrigger(owner.isPlayer1() ? StartTurnPlayer1 : StartTurnPlayer2, trigger.get());
}

//=========================================================
void DarkRitual::execute(Notification notification) {
    // Check if real notification type
    auto realNoti = dynamic_cast<TurnChangeNotification*>(&notification);
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
    owner.setMagic(owner.getMagic() + 1);
}
