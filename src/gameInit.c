#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/gameInit.h"
#include "../include/game.h"

void gameInit(Game *new_game, GameConfig *config)
{
    printf("\n--- INITIALIZING GAME ---\n");
    fflush(stdout);
    usleep(400000);

    Table new_table;
    Deck new_deck;
    initialize(&new_deck);

    printf("Shuffling 52-card deck... ");
    fflush(stdout);
    shuffle(&new_deck);
    usleep(600000);
    printf("Done.\n");
    fflush(stdout);
    usleep(400000);

    new_table.pot = 0;
    new_game->phase = PRE_FLOP;
    new_game->table = new_table;
    new_game->config = *config;
    new_game->deck = new_deck;

    int starting_chips = blind_table[config->blind_level].big_blind * 100;
    printf("Seating %d players and issuing %d chips each... ", config->num_of_players, starting_chips);
    fflush(stdout);
    usleep(600000);

    for (int i = 0; i < config->num_of_players; i++)
    {
        if (i == 0)
        {
            snprintf(new_game->players[i].name, sizeof(new_game->players[i].name), "You");
        }
        else
        {
            snprintf(new_game->players[i].name, sizeof(new_game->players[i].name), "Player %d", i);
        }
        new_game->players[i].chips = starting_chips;
        new_game->players[i].current_bet = 0;
        new_game->players[i].folded = false;
        new_game->players[i].is_all_in = false;
    }
    printf("Done.\n");
    fflush(stdout);
    usleep(400000);

    new_game->dealer_position = rand() % config->num_of_players;
    printf("Assigning Dealer button: %s is the Dealer [D].\n",
           new_game->players[new_game->dealer_position].name);
    fflush(stdout);
    usleep(700000);
}