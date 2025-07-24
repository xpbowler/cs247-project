#pragma once

enum Area {
    Deck,
    Hand,
    Board,
    Graveyard
};

enum TriggerType {
    EndTurn,
    StartTurn,
    MinionLeave,
    MinionEnter
};