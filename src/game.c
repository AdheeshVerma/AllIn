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
// int preFlopBetting(Game *game){

// }
