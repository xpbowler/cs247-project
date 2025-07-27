#include "apprenticeSummoner.h"
#include "player.h"

//=========================================================
ApprenticeSummoner::ApprenticeSummoner(Player& owner, Player& opponent) 
    : ActivatedMinion (APPRENTICE_SUMMONER_ACTIVATION_COST,
                       APPRENTICE_SUMMONER_ATK, 
                       APPRENTICE_SUMMONER_DEF,
                       owner, opponent, AS, "Apprentice Summoner") {

}


//=========================================================
void ApprenticeSummoner::useSkill() {
    owner.summonMinion()
}

