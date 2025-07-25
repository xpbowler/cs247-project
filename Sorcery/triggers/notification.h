#pragma once 

class Player;
class Minion;

// wrappers for notification that can be passed around in observer pattern

struct Notification {

};

struct TurnChangeNotification : public Notification {
    bool isStart;
    Player* player;
    TurnChangeNotification(bool isStart, Player* player) : isStart{isStart}, player{player} {}
};

struct MinionNotification : public Notification {
    Minion* minion; // the minion pointer that is entering/leaving play
    Player* player; // the player that the minion is under 
    MinionNotification(Minion* minion, Player* player) : minion {minion}, player{player} {}
};