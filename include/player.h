#ifndef ALLIN_PLAYER_H
#define ALLIN_PLAYER_H
#include <stdbool.h>
#include "card.h"

typedef struct
{
    char name[20];
    int chips;
    Card cards[2];
    int current_bet;
    bool folded;
    bool is_all_in;
} Player;
#endif

