#pragma once

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
