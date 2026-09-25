#include <stdio.h>
#include <stdlib.h>
#include "../include/card.h"
void displayCard(Card *card)
{
    if (card->rank == ACE)
        printf("A");
    else if (card->rank == TWO)
        printf("2");
    else if (card->rank == THREE)
        printf("3");
    else if (card->rank == FOUR)
        printf("4");
    else if (card->rank == FIVE)
        printf("5");
    else if (card->rank == SIX)
        printf("6");
    else if (card->rank == SEVEN)
        printf("7");
    else if (card->rank == EIGHT)
        printf("8");
    else if (card->rank == NINE)
        printf("9");
    else if (card->rank == TEN)
        printf("10");
    else if (card->rank == JACK)
        printf("J");
    else if (card->rank == QUEEN)
        printf("Q");
    else if (card->rank == KING)
        printf("K");

    // printf(" of ");

    if (card->suit == CLUBS)
        printf("♣ ");
    else if (card->suit == DIAMONDS)
        printf("♦ ");
    else if (card->suit == HEARTS)
        printf("♥ ");
    else if (card->suit == SPADES)
        printf("♠ ");
}