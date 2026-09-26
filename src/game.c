#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/game.h"
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

int preFlopBetting(Game *game)
{
    int smallBlind = blind_table[game->config.blind_level].small_blind;
    int bigBlind = blind_table[game->config.blind_level].big_blind;

    // fixed Betting: Blinds
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

    // optional betting: starts with player after Big Blind (Under the Gun)
    nextTurn(game);

    int current_highest_bet = bigBlind;
    int min_raise = bigBlind;

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
            // Human player turn
            printf("\n--- YOUR TURN (%s) ---\n", p->name);
            printf("Pot: %d | Your Chips: %d | Current Highest Bet: %d\n",
                   game->table.pot, p->chips, current_highest_bet);
            printf("Your Current Bet: %d | To Call: %d\n", p->current_bet, to_call);
            printf("Your Cards: ");
            displayCard(&p->cards[0]);
            printf(" ");
            displayCard(&p->cards[1]);
            printf("\n");

            while (1)
            {
                if (to_call == 0)
                {
                    printf("Choose action: [c] Check, [r] Raise, [f] Fold: ");
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
                            printf("Invalid raise amount. Must be between %d and %d.\n",
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
            // Computer player action
            printf("%s's turn... ", p->name);
            fflush(stdout);
            usleep(300000);

            if (to_call == 0)
            {
                printf("checks.\n");
                players_to_act--;
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
                    printf("calls %d (All-In)!\n", call_amount);
                }
                else
                {
                    printf("calls %d.\n", call_amount);
                }
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
