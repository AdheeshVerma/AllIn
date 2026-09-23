#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/deck.h"
#include "../include/gameConfig.h"
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
            printf("ENTERING GAME SETUP. CHOOSE YOUR GAME CONFIGURATIONS\n");
            GameConfig config;
            int num_of_players, blind;
            // Number of players selection
            while (1)
            {
                printf("Select Number Of players\n");
                printf("Press ENTER for random(4-6)\t\t\t Enter a number(2-9)\n");
                printf("Enter Your Choice:");
                fgets(input, sizeof(input), stdin);

                if (input[0] == '\n')
                {
                    num_of_players = 4 + rand() % 3;
                    break;
                }

                if (input[0] >= '2' && input[0] <= '9' && input[1] == '\n')
                {
                    num_of_players = input[0] - '0';
                    break;
                }

                printf("Invalid input. Enter a number from 2 to 9.\n");
            }
            printf("\nNumber of players: %d\n", num_of_players);
            // Blind Selection
            while (1)
            {
                printf("\nSelect Blind to play with (1,2,3)\n");

                for (int i = 0; i < BLIND_COUNT - 1; i++)
                {
                    printf("%d. %s (%d/%d)\n",
                           i + 1,
                           blind_table[i].name,
                           blind_table[i].small_blind,
                           blind_table[i].big_blind);
                }
                printf("Enter Your Choice: ");
                fgets(input, sizeof(input), stdin);
                if (input[0] >= '1' && (input[0] - '0' <= BLIND_COUNT) && input[1] == '\n')
                {
                    blind = (input[0] - '0') - 1;
                    break;
                }

                printf("Invalid input. Choose a valid blind.\n");
            }
            printf("Bet Selected: %s\n", blind_table[blind].name);
        }
        else if (input[0] == 'q')
        {
            printf("User Quitted");
            exit(1);
        }
    }
    return 0;
}