#include "standstill.h"
#include <notification.h>
#include <../minions/minion.h>
#include <../player.h>

//=========================================================
Standstill::Standstill(Player& owner, Player& opponent) : Ritual {STANDSTILL_COST, 
                                                                  STANDSTILL_ACTIVATION_COST, 
                                                                  STANDSTILL_CHARGES, 
                                                                  owner, opponent, STANDSTILL, STANDSTILL_DESC} {
   
}

//=========================================================
void Standstill::execute(Notification notification) {
    
    // Check if real notification type
    auto realNoti = dynamic_cast<MinionNotification*>(&notification);
    if (!realNoti) {
        return;
    }
    // Check if enough charges
    if (charges < activationCost) {
        return;
    }
    // Execute
    charges -= activationCost;
    auto minion = realNoti->minion;
    // Could maybe also make minion take dmg?
    if (!owner.moveCard(minion, Board, Graveyard)) {
        opponent.moveCard(minion, Board, Graveyard);
    }
}

