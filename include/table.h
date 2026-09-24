#ifndef ALLIN_TABLE_H
#define ALLIN_TABLE_H
#include "card.h"
#include "player.h"
#include "game.h"
typedef struct
{
    int pot;
    Card communityCards[5];
} Table;
#endif
