#include "auraOfPower.h"
#include <notification.h>

//=========================================================
AuraOfPower::AuraOfPower() : Ritual{1, 4} {
    
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
}

