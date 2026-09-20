#include <stdlib.h>
#include "../include/deck.h"
#include "../include/card.h"
void initialize(Deck *deck)
{
    int i = 0;
    for (Suit suit = CLUBS; suit <= SPADES; suit++)
    {
        for (Rank rank = ACE; rank <= KING; rank++)
        {
            deck->cards[i].rank = rank;
            deck->cards[i].suit = suit;
            i++;
        }
    }
}
// shuffeling using Fisher-Yates Algorithm
void shuffle(Deck *deck)
{
    for (int i = 51; i > 0; i--)
    {
        int j = rand() % (i + 1);

        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
    deck->top = 51;
}
Card deal(Deck *deck)
{
    if (deck->top < 0)
        exit(-1);
    return deck->cards[deck->top--];
}
