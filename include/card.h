#ifndef ALLIN_CARD_H
#define ALLIN_CARD_H

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
    Rank rank;
    Suit suit;
} Card;

#endif
