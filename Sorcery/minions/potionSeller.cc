#include "potionSeller.h"
#include <notification.h>

//=========================================================
PotionSeller::PotionSeller(Player &owner, Player &opponent)
    : TriggeredMinion(POTION_SELLER_ATK,
                      POTION_SELLER_DEF,
                      owner, opponent, "Potion Seller", PS)
{
    // TODO: set up trigger
}

//=========================================================
void PotionSeller::useSkill(Notification notification)
{
    // TODO
}
