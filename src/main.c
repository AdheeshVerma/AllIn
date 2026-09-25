#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/gameSetup.h"
#include "../include/gameInit.h"
#include "../include/game.h"
int main()
{
    // banner
    puts("╔══════════════════════════════════════════════════════════════════╗\n"
         "║                                                                  ║\n"
         "║                                                                  ║\n"
         "║            █████╗ ██╗     ██╗       ██╗███╗   ██╗                ║\n"
         "║           ██╔══██╗██║     ██║       ██║████╗  ██║                ║\n"
         "║           ███████║██║     ██║       ██║██╔██╗ ██║                ║\n"
         "║           ██╔══██╗██║     ██║       ██║██║╚██╗██║                ║\n"
         "║           ██║  ██║███████╗███████╗  ██║██║ ╚████║                ║\n"
         "║           ╚═╝  ╚═╝╚══════╝╚══════╝  ╚═╝╚═╝  ╚═══╝                ║\n"
         "║                                                                  ║\n"
         "║              ┌─────────────────────────────┐                     ║\n"
         "║              │ T E X A S   H O L D ' E M   │                     ║\n"
         "║              └─────────────────────────────┘                     ║\n"
         "║                                                                  ║\n"
         "║          ┌───┐ ┌───┐         ┌───┐ ┌───┐                         ║\n"
         "║          │A. │ │K. │ ...     │ 10│ │ 2 │                         ║\n"
         "║          │ ♠ │ │ ♥ │         │ ♦ │ │ ♣ │                         ║\n"
         "║          │ .A│ │ .K│         │ 10│ │ 2 │                         ║\n"
         "║          └───┘ └───┘         └───┘ └───┘                         ║\n"
         "║                                                                  ║\n"
         "║     ♣ ♦ ♥ ♠ ♣ ♦ ♥ ♠ ♣ ♦ ♥ ♠ ♣ ♦ ♥ ♠ ♣ ♦ ♥ ♠ ♣ ♦ ♥ ♠ ♣ ♦ ♥ ♠ ♣    ║\n"
         "║                                                                  ║\n"
         "║     [PRESS ENTER TO PLAY]                       [Q TO QUIT]      ║\n"
         "║                                                                  ║\n"
         "╚══════════════════════════════════════════════════════════════════╝");

    // Logic
    char input[100];
    srand((unsigned)time(NULL));
    printf("Enter Your Choice: ");
    while (1)
    {
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\n')
        {
            printf("Entering Game");
            for (int i = 0; i < 10; i++)
            {
                printf(".");
                fflush(stdout);
                sleep(0.8);
            }
            GameConfig config;
            gameSetup(&config);
            printf("Blind Selected is %s\n", blind_table[config.blind_level].name);
            printf("Total Number of players %d\n", config.num_of_players);
            Game newGame;
            gameInit(&newGame, &config);
            printf("Game initialized\n");
            printf("Current Game Phase: %d\n", newGame.phase);
            printf("Current Pot: %d\n", newGame.table.pot);
            printf("Top Card of deck is %d\n", newGame.deck.top);

            printf("Dealer is %d i.e %s", newGame.dealer_position, newGame.players[newGame.dealer_position].name);

            printf("\n======================Starting Game===================\n");
            dealHoleCards(&newGame);
            for (int i = 0; i < config.num_of_players; i++)
            {
                printf("Player %d name %s \tCurrent money: %d has cards ", i + 1, newGame.players[i].name, newGame.players[i].chips);
                displayCard(&(newGame.players[i].cards[0]));
                printf(" and ");
                displayCard(&(newGame.players[i].cards[1]));
                printf("\n");
            }
        }
        else if (input[0] == 'q')
        {
            printf("User Quitted");
            exit(1);
        }
    }
    return 0;
}