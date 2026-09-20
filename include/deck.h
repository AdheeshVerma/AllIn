#ifndef ALLIN_DECK_H
#define ALLIN_DECK_H
#include "card.h"

typedef struct
{
    Card cards[52];
    int top;
} Deck;

void initialize(Deck *deck);
void shuffle(Deck *deck);
Card deal(Deck *deck);

#endif