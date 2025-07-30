#include "potionSeller.h"
#include <notification.h>
#include <trigger.h>
#include <player.h>

//=========================================================
PotionSeller::PotionSeller(Player &owner, Player &opponent)
    : TriggeredMinion(POTION_SELLER_ATK,
                      POTION_SELLER_DEF,
                      owner, opponent, POTION_SELLER, POTION_SELLER_DESC, 
                      owner.isPlayer1() ? EndTurnPlayer1 : EndTurnPlayer2, POTION_SELLER_COST, PS)
{
    trigger = std::make_unique<Trigger> (this);
}

//=========================================================
void PotionSeller::useSkill(const Notification& notification)
{
    // check for notification type 
    auto realNoti = dynamic_cast<const TurnChangeNotification*> (&notification);
    if (!realNoti) return;
    if (realNoti->isStart) return;
    if (realNoti->player != &owner) return;
    // assumes this only affects board 
    applyEnchantment(UseAbility);
    if (canUseAbility) {
        for (const auto& card : owner.getBoard()) {
            auto minion = dynamic_cast<Minion*> (card.get());
            if (!minion) continue;
            minion->gainStats(0, 1);
        }
    }
    canUseAbility = true;
}
