#include "novicePyromancer.h"

//=========================================================
NovicePyromancer::NovicePyromancer(Player &owner, Player &opponent)
    : ActivatedMinion(NOVICE_PYROMANCER_ACTIVATION_COST,
                      NOVICE_PYROMANCER_ATK,
                      NOVICE_PYROMANCER_DEF,
                      owner, opponent, NP, "Novice Pyromancer")
{

}

//=========================================================
void NovicePyromancer::useSkill()
{
    // TODO
}
