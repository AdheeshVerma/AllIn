#include "../include/handEvaluator.h"
#include <stdio.h>
#include <string.h>

static const char *RANK_NAMES[] = {"",     "",     "Two",   "Three", "Four",
                                   "Five", "Six",  "Seven", "Eight", "Nine",
                                   "Ten",  "Jack", "Queen", "King",  "Ace"};

int getCardRankValue(Rank rank) {
  if (rank == ACE)
    return 14;
  return (int)rank;
}

const char *getRankName(int rank_val) {
  if (rank_val >= 2 && rank_val <= 14) {
    return RANK_NAMES[rank_val];
  }
  return "Unknown";
}

int compareHands(const HandValue *h1, const HandValue *h2) {
  if (h1->type > h2->type)
    return 1;
  if (h1->type < h2->type)
    return -1;

  for (int i = 0; i < 5; i++) {
    if (h1->ranks[i] > h2->ranks[i])
      return 1;
    if (h1->ranks[i] < h2->ranks[i])
      return -1;
  }
  return 0;
}

typedef struct {
  int rank;
  int count;
} RankFreq;

HandValue evaluate5CardHand(const Card cards[5]) {
  HandValue result;
  memset(&result, 0, sizeof(result));

  int vals[5];
  for (int i = 0; i < 5; i++) {
    vals[i] = getCardRankValue(cards[i].rank);
  }

  // sort descending on values
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 5; j++) {
      if (vals[i] < vals[j]) {
        int tmp = vals[i];
        vals[i] = vals[j];
        vals[j] = tmp;
      }
    }
  }

  bool is_flush =
      (cards[0].suit == cards[1].suit && cards[1].suit == cards[2].suit &&
       cards[2].suit == cards[3].suit && cards[3].suit == cards[4].suit);

  bool is_straight = false;
  int straight_high = 0;

  if (vals[0] - 1 == vals[1] && vals[1] - 1 == vals[2] &&
      vals[2] - 1 == vals[3] && vals[3] - 1 == vals[4]) {
    is_straight = true;
    straight_high = vals[0];
  } else if (vals[0] == 14 && vals[1] == 5 && vals[2] == 4 && vals[3] == 3 &&
             vals[4] == 2) {
    is_straight = true;
    straight_high = 5;
  }

  // Straight Flush & Royal Flush
  if (is_flush && is_straight) {
    if (straight_high == 14) {
      result.type = ROYAL_FLUSH;
      result.ranks[0] = 14;
      snprintf(result.description, sizeof(result.description), "Royal Flush");
    } else {
      result.type = STRAIGHT_FLUSH;
      result.ranks[0] = straight_high;
      snprintf(result.description, sizeof(result.description),
               "Straight Flush (%s High)", getRankName(straight_high));
    }
    return result;
  }

  // counting freq of ranks
  RankFreq freqs[5];
  int num_freqs = 0;

  for (int i = 0; i < 5; i++) {
    int r = vals[i];
    int idx = -1;
    for (int k = 0; k < num_freqs; k++) {
      if (freqs[k].rank == r) {
        idx = k;
        break;
      }
    }
    if (idx >= 0) {
      freqs[idx].count++;
    } else {
      freqs[num_freqs].rank = r;
      freqs[num_freqs].count = 1;
      num_freqs++;
    }
  }

  // sort descending by freq then by rank
  for (int i = 0; i < num_freqs - 1; i++) {
    for (int j = i + 1; j < num_freqs; j++) {
      if (freqs[i].count < freqs[j].count ||
          (freqs[i].count == freqs[j].count && freqs[i].rank < freqs[j].rank)) {
        RankFreq tmp = freqs[i];
        freqs[i] = freqs[j];
        freqs[j] = tmp;
      }
    }
  }

  // Four of a kind
  if (freqs[0].count == 4) {
    result.type = FOUR_OF_A_KIND;
    result.ranks[0] = freqs[0].rank;
    result.ranks[1] = freqs[1].rank;
    snprintf(result.description, sizeof(result.description),
             "Four of a Kind (%ss)", getRankName(freqs[0].rank));
    return result;
  }

  // Full House
  if (freqs[0].count == 3 && freqs[1].count == 2) {
    result.type = FULL_HOUSE;
    result.ranks[0] = freqs[0].rank;
    result.ranks[1] = freqs[1].rank;
    snprintf(result.description, sizeof(result.description),
             "Full House (%ss full of %ss)", getRankName(freqs[0].rank),
             getRankName(freqs[1].rank));
    return result;
  }

  // Flush
  if (is_flush) {
    result.type = FLUSH;
    for (int i = 0; i < 5; i++) {
      result.ranks[i] = vals[i];
    }
    snprintf(result.description, sizeof(result.description), "Flush (%s High)",
             getRankName(vals[0]));
    return result;
  }

  // Straight
  if (is_straight) {
    result.type = STRAIGHT;
    if (straight_high == 5) {
      result.ranks[0] = 5;
      result.ranks[1] = 4;
      result.ranks[2] = 3;
      result.ranks[3] = 2;
      result.ranks[4] = 1; // ace = 1
    } else {
      for (int i = 0; i < 5; i++) {
        result.ranks[i] = straight_high - i;
      }
    }
    snprintf(result.description, sizeof(result.description),
             "Straight (%s High)", getRankName(straight_high));
    return result;
  }

  // Three of a Kind
  if (freqs[0].count == 3) {
    result.type = THREE_OF_A_KIND;
    result.ranks[0] = freqs[0].rank;
    result.ranks[1] = freqs[1].rank;
    result.ranks[2] = freqs[2].rank;
    snprintf(result.description, sizeof(result.description),
             "Three of a Kind (%ss)", getRankName(freqs[0].rank));
    return result;
  }

  // Two Pair
  if (freqs[0].count == 2 && freqs[1].count == 2) {
    result.type = TWO_PAIR;
    result.ranks[0] = freqs[0].rank;
    result.ranks[1] = freqs[1].rank;
    result.ranks[2] = freqs[2].rank;
    snprintf(result.description, sizeof(result.description),
             "Two Pair (%ss and %ss)", getRankName(freqs[0].rank),
             getRankName(freqs[1].rank));
    return result;
  }

  // One Pair
  if (freqs[0].count == 2) {
    result.type = ONE_PAIR;
    result.ranks[0] = freqs[0].rank;
    result.ranks[1] = freqs[1].rank;
    result.ranks[2] = freqs[2].rank;
    result.ranks[3] = freqs[3].rank;
    snprintf(result.description, sizeof(result.description), "Pair of %ss",
             getRankName(freqs[0].rank));
    return result;
  }

  // High Card
  result.type = HIGH_CARD;
  for (int i = 0; i < 5; i++) {
    result.ranks[i] = vals[i];
  }
  snprintf(result.description, sizeof(result.description), "High Card (%s)",
           getRankName(vals[0]));
  return result;
}

HandValue evaluateBestHand(const Card *cards, int num_cards) {
  if (num_cards == 2) {
    HandValue val;
    memset(&val, 0, sizeof(val));
    int r0 = getCardRankValue(cards[0].rank);
    int r1 = getCardRankValue(cards[1].rank);
    if (r0 < r1) {
      int tmp = r0;
      r0 = r1;
      r1 = tmp;
    }
    if (r0 == r1) {
      val.type = ONE_PAIR;
      val.ranks[0] = r0;
      snprintf(val.description, sizeof(val.description), "Pocket Pair of %ss",
               getRankName(r0));
    } else {
      val.type = HIGH_CARD;
      val.ranks[0] = r0;
      val.ranks[1] = r1;
      snprintf(val.description, sizeof(val.description), "%s High",
               getRankName(r0));
    }
    return val;
  }

  if (num_cards == 5) {
    return evaluate5CardHand(cards);
  }

  HandValue bestHand;
  memset(&bestHand, 0, sizeof(bestHand));
  bool first = true;

  if (num_cards >= 5) {
    for (int i = 0; i < num_cards - 4; i++) {
      for (int j = i + 1; j < num_cards - 3; j++) {
        for (int k = j + 1; k < num_cards - 2; k++) {
          for (int l = k + 1; l < num_cards - 1; l++) {
            for (int m = l + 1; m < num_cards; m++) {
              Card combo[5] = {cards[i], cards[j], cards[k], cards[l],
                               cards[m]};
              HandValue current = evaluate5CardHand(combo);
              if (first || compareHands(&current, &bestHand) > 0) {
                bestHand = current;
                first = false;
              }
            }
          }
        }
      }
    }
  }

  return bestHand;
}
