#ifndef ALLIN_PLAYER_H
#define ALLIN_PLAYER_H
#include "card.h"
typedef struct Player
{
    char *name;
    int chips;
    Card cards[2];
};
#endif
