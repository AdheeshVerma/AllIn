#ifndef ALLIN_HAND_EVALUATOR_H
#define ALLIN_HAND_EVALUATOR_H

#include "card.h"
#include <stdbool.h>

typedef enum {
  HIGH_CARD = 1,
  ONE_PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  STRAIGHT,
  FLUSH,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  STRAIGHT_FLUSH,
  ROYAL_FLUSH
} HandRankType;

typedef struct {
  HandRankType type;
  int ranks[5];
  char description[64];
} HandValue;

// value for card in the rank
int getCardRankValue(Rank rank);

// getting the name of the rank
const char *getRankName(int rank_val);

// compare two hand values
int compareHands(const HandValue *h1, const HandValue *h2);

HandValue evaluate5CardHand(const Card cards[5]);

HandValue evaluateBestHand(const Card *cards, int num_cards);

#endif
