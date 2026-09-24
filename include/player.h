#ifndef ALLIN_PLAYER_H
#define ALLIN_PLAYER_H
#include "card.h"
typedef struct
{
    char name[9];
    int chips;
    Card cards[2];
} Player;
#endif
