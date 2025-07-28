#include "auraOfPower.h"
#include <notification.h>
#include <../minions/minion.h>

//=========================================================
AuraOfPower::AuraOfPower(Player& owner, Player& opponent) : Ritual{1, 4, owner, opponent} {
    
}

//=========================================================
void AuraOfPower::execute(Notification notification) {
    // check if it is the correct notification type 
    auto realNoti = dynamic_cast<MinionNotification*> (&notification);
    if (!realNoti) {
        return;
    }
    // check if minion is on the same side or not
    if (&owner != realNoti->player) {
        return;
    }
    // now, check if there is enough charges, if not return
    if (charges < activationCost) {
        return;
    }
    // finally, execute the ability and subtract off the charges
    charges -= activationCost;
    auto minion = realNoti->minion;
    minion->gainStats(1, 1);
}

