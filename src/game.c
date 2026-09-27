#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/game.h"
#include "../include/handEvaluator.h"

void dealHoleCards(Game *game)
{
    for (int i = 0; i < game->config.num_of_players; i++)
    {
        Card c1 = deal(&game->deck);
        Card c2 = deal(&game->deck);
        game->players[i].cards[0] = c1;
        game->players[i].cards[1] = c2;
    }
}

void dealFlop(Game *game)
{
    game->phase = FLOP;
    deal(&game->deck);
    game->table.communityCards[0] = deal(&game->deck);
    game->table.communityCards[1] = deal(&game->deck);
    game->table.communityCards[2] = deal(&game->deck);
}

void dealTurn(Game *game)
{
    game->phase = TURN;
    deal(&game->deck);
    game->table.communityCards[3] = deal(&game->deck);
}

void dealRiver(Game *game)
{
    game->phase = RIVER;
    deal(&game->deck);
    game->table.communityCards[4] = deal(&game->deck);
}

void displayCommunityCards(Game *game)
{
    printf("Community Cards: ");
    int count = 0;
    if (game->phase == FLOP)
        count = 3;
    else if (game->phase == TURN)
        count = 4;
    else if (game->phase >= RIVER)
        count = 5;

    for (int i = 0; i < count; i++)
    {
        displayCard(&game->table.communityCards[i]);
        printf(" ");
    }
    printf("\n");
}

void nextTurn(Game *game)
{
    game->current_player = (game->current_player + 1) % game->config.num_of_players;
}

static int countActivePlayers(Game *game)
{
    int count = 0;
    for (int i = 0; i < game->config.num_of_players; i++)
    {
        if (!game->players[i].folded)
        {
            count++;
        }
    }
    return count;
}

static int runBettingRound(Game *game, int current_highest_bet, int min_raise)
{
    int players_to_act = 0;
    for (int i = 0; i < game->config.num_of_players; i++)
    {
        if (!game->players[i].folded && !game->players[i].is_all_in)
        {
            players_to_act++;
        }
    }

    char input[100];

    while (players_to_act > 0 && countActivePlayers(game) > 1)
    {
        Player *p = &game->players[game->current_player];

        if (p->folded || p->is_all_in)
        {
            nextTurn(game);
            continue;
        }

        int to_call = current_highest_bet - p->current_bet;
        if (to_call < 0)
            to_call = 0;

        if (game->current_player == 0)
        {
            printf("\n--- YOUR TURN (%s) ---\n", p->name);
            printf("Pot: %d | Your Chips: %d | Current Bet to Call: %d\n",
                   game->table.pot, p->chips, to_call);
            printf("Your Cards: ");
            displayCard(&p->cards[0]);
            printf(" ");
            displayCard(&p->cards[1]);
            if (game->phase > PRE_FLOP)
            {
                printf(" | Board: ");
                int c_count = (game->phase == FLOP) ? 3 : (game->phase == TURN) ? 4 : 5;
                for (int c = 0; c < c_count; c++)
                {
                    displayCard(&game->table.communityCards[c]);
                    printf(" ");
                }
            }
            printf("\n");

            while (1)
            {
                if (to_call == 0)
                {
                    printf("Choose action: [c] Check, [r] Bet, [f] Fold: ");
                }
                else
                {
                    printf("Choose action: [c] Call (%d), [r] Raise, [f] Fold: ", to_call);
                }

                if (!fgets(input, sizeof(input), stdin))
                    continue;

                char choice = input[0];
                if (choice == 'f' || choice == 'F')
                {
                    p->folded = true;
                    printf("You folded.\n");
                    players_to_act--;
                    break;
                }
                else if (choice == 'c' || choice == 'C')
                {
                    if (to_call == 0)
                    {
                        printf("You checked.\n");
                    }
                    else
                    {
                        int call_amount = (p->chips < to_call) ? p->chips : to_call;
                        p->chips -= call_amount;
                        p->current_bet += call_amount;
                        game->table.pot += call_amount;
                        if (p->chips == 0)
                        {
                            p->is_all_in = true;
                            printf("You called %d (All-In)!\n", call_amount);
                        }
                        else
                        {
                            printf("You called %d.\n", call_amount);
                        }
                    }
                    players_to_act--;
                    break;
                }
                else if (choice == 'r' || choice == 'R')
                {
                    int min_total_bet = current_highest_bet + min_raise;
                    int max_total_bet = p->current_bet + p->chips;

                    if (p->chips <= to_call)
                    {
                        printf("You don't have enough chips to raise. Call or fold instead.\n");
                        continue;
                    }

                    if (max_total_bet < min_total_bet)
                    {
                        min_total_bet = max_total_bet;
                    }

                    printf("Enter total bet amount (min %d, max %d): ", min_total_bet, max_total_bet);
                    if (fgets(input, sizeof(input), stdin))
                    {
                        int raise_total = atoi(input);
                        if (raise_total < min_total_bet || raise_total > max_total_bet)
                        {
                            printf("Invalid amount. Must be between %d and %d.\n",
                                   min_total_bet, max_total_bet);
                            continue;
                        }

                        int additional_chips = raise_total - p->current_bet;
                        p->chips -= additional_chips;
                        p->current_bet = raise_total;
                        game->table.pot += additional_chips;
                        if (p->chips == 0)
                        {
                            p->is_all_in = true;
                            printf("You raised to %d (All-In)!\n", raise_total);
                        }
                        else
                        {
                            printf("You raised to %d.\n", raise_total);
                        }

                        min_raise = raise_total - current_highest_bet;
                        current_highest_bet = raise_total;

                        players_to_act = 0;
                        for (int k = 0; k < game->config.num_of_players; k++)
                        {
                            if (k != game->current_player && !game->players[k].folded && !game->players[k].is_all_in)
                            {
                                players_to_act++;
                            }
                        }
                        break;
                    }
                }
                else
                {
                    printf("Invalid choice. Enter 'c', 'r', or 'f'.\n");
                }
            }
        }
        else
        {
            printf("%s's turn... ", p->name);
            fflush(stdout);
            usleep(300000);

            if (to_call == 0)
            {
                int can_bet = (p->chips >= min_raise);
                int does_bet = can_bet && (rand() % 100 < 20);

                if (does_bet)
                {
                    int bet_amount = min_raise;
                    p->chips -= bet_amount;
                    p->current_bet = bet_amount;
                    game->table.pot += bet_amount;
                    current_highest_bet = bet_amount;
                    min_raise = bet_amount;

                    if (p->chips == 0)
                    {
                        p->is_all_in = true;
                        printf("bets %d (All-In)!\n", bet_amount);
                    }
                    else
                    {
                        printf("bets %d.\n", bet_amount);
                    }

                    players_to_act = 0;
                    for (int k = 0; k < game->config.num_of_players; k++)
                    {
                        if (k != game->current_player && !game->players[k].folded && !game->players[k].is_all_in)
                        {
                            players_to_act++;
                        }
                    }
                }
                else
                {
                    printf("checks.\n");
                    players_to_act--;
                }
            }
            else if (p->chips >= to_call)
            {
                p->chips -= to_call;
                p->current_bet += to_call;
                game->table.pot += to_call;
                if (p->chips == 0)
                {
                    p->is_all_in = true;
                    printf("calls %d (All-In)!\n", to_call);
                }
                else
                {
                    printf("calls %d.\n", to_call);
                }
                players_to_act--;
            }
            else
            {
                p->folded = true;
                printf("folds.\n");
                players_to_act--;
            }
        }

        nextTurn(game);
    }

    if (countActivePlayers(game) == 1)
    {
        for (int i = 0; i < game->config.num_of_players; i++)
        {
            if (!game->players[i].folded)
            {
                printf("\nAll other players folded! %s wins the pot of %d chips!\n",
                       game->players[i].name, game->table.pot);
                game->players[i].chips += game->table.pot;
                game->table.pot = 0;
                return 0;
            }
        }
    }

    for (int i = 0; i < game->config.num_of_players; i++)
    {
        game->players[i].current_bet = 0;
    }

    return 1;
}

int preFlopBetting(Game *game)
{
    int smallBlind = blind_table[game->config.blind_level].small_blind;
    int bigBlind = blind_table[game->config.blind_level].big_blind;

    game->current_player = game->dealer_position;

    // Small blind
    nextTurn(game);
    int sb_player = game->current_player;
    int sb_amount = (game->players[sb_player].chips < smallBlind)
                        ? game->players[sb_player].chips
                        : smallBlind;
    game->players[sb_player].chips -= sb_amount;
    game->players[sb_player].current_bet = sb_amount;
    game->table.pot += sb_amount;
    if (game->players[sb_player].chips == 0)
    {
        game->players[sb_player].is_all_in = true;
    }
    printf("%s posts Small Blind: %d\n", game->players[sb_player].name, sb_amount);
    fflush(stdout);
    usleep(500000);

    // Big blind
    nextTurn(game);
    int bb_player = game->current_player;
    int bb_amount = (game->players[bb_player].chips < bigBlind)
                        ? game->players[bb_player].chips
                        : bigBlind;
    game->players[bb_player].chips -= bb_amount;
    game->players[bb_player].current_bet = bb_amount;
    game->table.pot += bb_amount;
    if (game->players[bb_player].chips == 0)
    {
        game->players[bb_player].is_all_in = true;
    }
    printf("%s posts Big Blind: %d\n", game->players[bb_player].name, bb_amount);
    fflush(stdout);
    usleep(500000);

    // Action starts with player after Big Blind
    nextTurn(game);

    return runBettingRound(game, bigBlind, bigBlind);
}

int postFlopBetting(Game *game)
{
    int bigBlind = blind_table[game->config.blind_level].big_blind;

    game->current_player = game->dealer_position;
    nextTurn(game);

    return runBettingRound(game, 0, bigBlind);
}

void showdown(Game *game)
{
    game->phase = SHOWDOWN;
    printf("\n======================= SHOWDOWN =======================\n");
    displayCommunityCards(game);
    printf("\n");

    int best_player_indices[MAX_PLAYERS];
    int num_winners = 0;
    HandValue best_value;
    memset(&best_value, 0, sizeof(best_value));

    for (int i = 0; i < game->config.num_of_players; i++)
    {
        if (game->players[i].folded)
            continue;

        Card all_cards[7];
        all_cards[0] = game->players[i].cards[0];
        all_cards[1] = game->players[i].cards[1];
        for (int c = 0; c < 5; c++)
        {
            all_cards[2 + c] = game->table.communityCards[c];
        }

        HandValue hand_val = evaluateBestHand(all_cards, 7);

        printf("%s shows: ", game->players[i].name);
        displayCard(&game->players[i].cards[0]);
        printf(" ");
        displayCard(&game->players[i].cards[1]);
        printf(" -> %s\n", hand_val.description);

        if (num_winners == 0)
        {
            best_value = hand_val;
            best_player_indices[0] = i;
            num_winners = 1;
        }
        else
        {
            int cmp = compareHands(&hand_val, &best_value);
            if (cmp > 0)
            {
                best_value = hand_val;
                best_player_indices[0] = i;
                num_winners = 1;
            }
            else if (cmp == 0)
            {
                best_player_indices[num_winners++] = i;
            }
        }
    }

    if (num_winners == 1)
    {
        int winner = best_player_indices[0];
        printf("\nWinner: %s with %s! Wins %d chips!\n",
               game->players[winner].name, best_value.description, game->table.pot);
        game->players[winner].chips += game->table.pot;
        game->table.pot = 0;
    }
    else if (num_winners > 1)
    {
        int split_amount = game->table.pot / num_winners;
        printf("\nTie between %d players! Each wins %d chips:\n", num_winners, split_amount);
        for (int w = 0; w < num_winners; w++)
        {
            int p_idx = best_player_indices[w];
            game->players[p_idx].chips += split_amount;
            printf("  - %s (%s)\n", game->players[p_idx].name, best_value.description);
        }
        game->table.pot = 0;
    }
}
