#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/gameInit.h"
#include "../include/game.h"
void gameInit(Game *new_game, GameConfig *config)
{

    Table new_table;
    Deck new_deck;
    initialize(&new_deck);
    shuffle(&new_deck);

    new_table.pot = 0;
    new_game->phase = PRE_FLOP;
    new_game->table = new_table;
    new_game->config = *config;
    new_game->deck = new_deck;
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
        new_game->players[i].chips = blind_table[config->blind_level].big_blind * 100;
        new_game->players[i].current_bet = 0;
        new_game->players[i].folded = false;
        new_game->players[i].is_all_in = false;
    }
    new_game->dealer_position = rand() % config->num_of_players;
}