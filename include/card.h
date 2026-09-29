#ifndef ALLIN_CARD_H
#define ALLIN_CARD_H
#include <stdint.h>
#include <stdio.h>

typedef enum
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
} Suit;
typedef enum
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING = 13,
} Rank;

typedef struct
{
    uint8_t suit :2;
    uint8_t rank :4;
} Card;

void displayCard(Card *card);
#endif
