#ifndef ALLIN_GAME_H
#define ALLIN_GAME_H
#include "deck.h"
#include "table.h"
#include "player.h"
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
void dealFlop(Game *game);
void dealTurn(Game *game);
void dealRiver(Game *game);
void displayCommunityCards(Game *game);
void nextTurn(Game *game);
int preFlopBetting(Game *game);
int postFlopBetting(Game *game);
void showdown(Game *game);
void startNewHand(Game *game);

#endif