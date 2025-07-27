#pragma once

// CONSTANTS
const int STARTING_LIFE = 20;
const int STARTING_MAGIC = 3;
const int STARTING_NUM_CARDS = 5;
const int AIR_ELEMENTAL_ATK = 1;
const int AIR_ELEMENTAL_DEF = 1;
const int AIR_ELEMENTAL_COST = 0;
const int EARTH_ELEMENTAL_ATK = 4;
const int EARTH_ELEMENTAL_DEF = 4;
const int EARTH_ELEMENTAL_COST = 3;
const int BONE_GOLEM_ATK = 1;
const int BONE_GOLEM_DEF = 3;
const int BONE_GOLEM_COST = 2;
const int FIRE_ELEMENTAL_ATK = 2;
const int FIRE_ELEMENTAL_DEF = 2;
const int FIRE_ELEMENTAL_COST = 2;
const int POTION_SELLER_ATK = 1;
const int POTION_SELLER_DEF = 3;
const int POTION_SELLER_COST = 2;
const int NOVICE_PYROMANCER_ATK = 0;
const int NOVICE_PYROMANCER_DEF = 1;
const int NOVICE_PYROMANCER_COST = 1;
const int NOVICE_PYROMANCER_ACTIVATION_COST = 1;
const int APPRENTICE_SUMMONER_ATK = 1;
const int APPRENTICE_SUMMONER_DEF = 1;
const int APPRENTICE_SUMMONER_COST = 1;
const int APPRENTICE_SUMMONER_ACTIVATION_COST = 1;
const int MASTER_SUMMONER_ATK = 2;
const int MASTER_SUMMONER_DEF = 3;
const int MASTER_SUMMONER_COST = 3;
const int MASTER_SUMMONER_ACTIVATION_COST = 2;


// Card name constants
inline constexpr const char* AIR_ELEMENTAL = "Air Elemental";
inline constexpr const char* EARTH_ELEMENTAL = "Earth Elemental";
inline constexpr const char* FIRE_ELEMENTAL = "Fire Elemental";
inline constexpr const char* POTION_SELLER = "Potion Seller";
inline constexpr const char* NOVICE_PYROMANCER = "Novice Pyromancer";
inline constexpr const char* APPRENTICE_SUMMONER = "Apprentice Summoner";
inline constexpr const char* MASTER_SUMMONER = "Master Summoner";
inline constexpr const char* BANISH = "Banish";
inline constexpr const char* UNSUMMON = "Unsummon";
inline constexpr const char* RECHARGE = "Recharge";
inline constexpr const char* DISENCHANT = "Disenchant";
inline constexpr const char* RAISE_DEAD = "Raise Dead";
inline constexpr const char* BLIZZARD = "Blizzard";
inline constexpr const char* GIANT_STRENGTH = "Giant Strength";
inline constexpr const char* MAGIC_FATIGUE = "Magic Fatigue";
inline constexpr const char* SILENCE = "Silence";
inline constexpr const char* DARK_RITUAL = "Dark Ritual";
inline constexpr const char* AURA_OF_POWER = "Aura of Power";
inline constexpr const char* STANDSTILL = "Standstill";

// Enums
enum Area {
    Deck,
    Hand,
    Board,
    Graveyard
};

enum TriggerType {
    EndTurnPlayer1,
    EndTurnPlayer2,
    StartTurnPlayer1,
    StartTurnPlayer2,
    MinionLeave,
    MinionEnter
};

enum MinionType {
    AE, // air elemental
    EE, // earth elemental 
    NP, // novice pyromancer 
    MS, // master summoner
    AS, // apprentice summoner
    BG, // bone golem
    FE, // fire elemental 
    PS // potion seller
};