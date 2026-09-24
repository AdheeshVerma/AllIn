#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/gameSetup.h"
const BlindInfo blind_table[] = {
    {CASUAL_10_20, "Casual", 10, 20},
    {HIGH_STAKES_50_100, "High Stakes", 50, 100},
    {NO_MERCY_500_1000, "NO MERCY", 500, 1000},
};
void gameSetup(GameConfig *config)
{
    char input[100];

    printf("ENTERING GAME SETUP. CHOOSE YOUR GAME CONFIGURATIONS\n");
    int num_of_players, blind;
    // Number of players selection
    while (1)
    {
        printf("Select Number Of opponents\n");
        printf("Press ENTER for random(3-5)\t\t\t Enter a number(2-9)\n");
        printf("Enter Your Choice:");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            num_of_players = 3 + rand() % 2;
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
    config->blind_level = blind;
    config->num_of_players = num_of_players;
}
