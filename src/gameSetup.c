#define _DEFAULT_SOURCE
#include "../include/gameSetup.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
const BlindInfo blind_table[] = {
    {CASUAL_10_20, "Casual", 10, 20},
    {HIGH_STAKES_50_100, "High Stakes", 50, 100},
    {NO_MERCY_500_1000, "NO MERCY", 500, 1000},
};
void gameSetup(GameConfig *config) {
  char input[100];
  
  printf("\n=======================================================\n");
  printf("               TABLE SETUP & CONFIGURATION             \n");
  printf("=======================================================\n");
  fflush(stdout);
  usleep(500000);

  int num_of_players, blind;
  // Number of players selection
  while (1) {
    printf("Select Number Of Opponents:\n");
    printf("  [ENTER] Random (3-5 opponents)\n");
    printf("  [2 - 8] Enter a number\n");
    printf("Enter Your Choice: ");
    fflush(stdout);
    if (!fgets(input, sizeof(input), stdin)) {
      exit(0);
    }

    if (input[0] == '\n') {
      int opponents = (3 + rand() % 2);
      printf("Selecting random table size");
      for (int d = 0; d < 3; d++) {
        usleep(250000);
        printf(".");
        fflush(stdout);
      }
      printf(" %d opponents selected!\n", opponents);
      fflush(stdout);
      num_of_players = opponents + 1;
      usleep(500000);
      break;
    }

    if (input[0] >= '2' && input[0] <= '8' && input[1] == '\n') {
      int opponents = input[0] - '0';
      printf("Setting up table for %d opponents...\n", opponents);
      fflush(stdout);
      usleep(500000);
      num_of_players = opponents + 1;
      break;
    }

    printf("Invalid input. Enter a number from 2 to 8 or press ENTER.\n\n");
    usleep(400000);
  }

  printf("\nTotal players at table: %d (You + %d opponents)\n", num_of_players, num_of_players - 1);
  fflush(stdout);
  usleep(600000);

  // Blind Selection
  while (1) {
    printf("\nSelect Blind Structure:\n");

    for (int i = 0; i < BLIND_COUNT - 1; i++) {
      printf("  [%d] %-12s (Blinds: %d/%d)\n",
             i + 1,
             blind_table[i].name,
             blind_table[i].small_blind,
             blind_table[i].big_blind);
    }
    printf("Enter Your Choice (1-3): ");
    fflush(stdout);
    if (!fgets(input, sizeof(input), stdin)) {
      exit(0);
    }
    if (input[0] >= '1' && (input[0] - '0' <= BLIND_COUNT - 1) &&
        input[1] == '\n') {
      blind = (input[0] - '0') - 1;
      printf("Blind set to %s (%d/%d).\n",
             blind_table[blind].name,
             blind_table[blind].small_blind,
             blind_table[blind].big_blind);
      fflush(stdout);
      usleep(600000);
      break;
    }

    printf("Invalid input. Choose 1, 2, or 3.\n");
    usleep(400000);
  }
  config->blind_level = blind;
  config->num_of_players = num_of_players;

  printf("\nTable configured! Initializing table...\n");
  fflush(stdout);
  usleep(700000);
}
