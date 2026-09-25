#ifndef ALLIN_GAME_H
#define ALLIN_GAME_H
#include "deck.h"
#include "table.h"
#include "gameConfig.h"
#define MAX_PLAYERS 9

typedef enum
{
    PRE_FLOP = 1,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
} Phase;
typedef struct
{
    Phase phase;
    Table table;
    GameConfig config;
    Deck deck;
    int current_player;
    int dealer_position;
    Player players[MAX_PLAYERS];

} Game;
void dealHoleCards(Game *game);
#endif