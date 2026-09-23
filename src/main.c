#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/deck.h"
#include "../include/gameSetup.h"
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
            printf("%d", config.blind_level);
            printf("%d", config.num_of_players);
        }
        else if (input[0] == 'q')
        {
            printf("User Quitted");
            exit(1);
        }
    }
    return 0;
}