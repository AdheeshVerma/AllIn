#define _DEFAULT_SOURCE
#include "../include/game.h"
#include "../include/gameInit.h"
#include "../include/gameSetup.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int main() {
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
  while (1) {
    if (!fgets(input, sizeof(input), stdin))
      break;
    if (input[0] == '\n') {
      printf("Entering Game");
      for (int i = 0; i < 10; i++) {
        printf(".");
        fflush(stdout);
        usleep(80000);
      }
      printf("\n");
      GameConfig config;
      gameSetup(&config);

      Game newGame;
      gameInit(&newGame, &config);

      int hand_number = 1;

      while (1) {
        printf("\n====================== Starting Hand #%d ======================\n", hand_number);
        fflush(stdout);
        usleep(600000);

        printf("Dealing hole cards...\n");
        fflush(stdout);
        dealHoleCards(&newGame);
        usleep(700000);

        printf("\n==================== Pre-Flop Betting ====================\n");
        fflush(stdout);
        usleep(500000);
        int hand_active = preFlopBetting(&newGame);

        if (hand_active) {
          printf("\n--- Pre-Flop Betting Complete ---\n");
          printf("Pot is now: %d\n", newGame.table.pot);

          printf("\n======================== The Flop =======================\n");
          dealFlop(&newGame);
          displayCommunityCards(&newGame);
          hand_active = postFlopBetting(&newGame);
        }

        if (hand_active) {
          printf("\n--- Flop Betting Complete ---\n");
          printf("Pot is now: %d\n", newGame.table.pot);

          printf("\n======================== The Turn =======================\n");
          dealTurn(&newGame);
          displayCommunityCards(&newGame);
          hand_active = postFlopBetting(&newGame);
        }

        if (hand_active) {
          printf("\n--- Turn Betting Complete ---\n");
          printf("Pot is now: %d\n", newGame.table.pot);

          printf("\n======================== The River ======================\n");
          dealRiver(&newGame);
          displayCommunityCards(&newGame);
          hand_active = postFlopBetting(&newGame);
        }

        if (hand_active) {
          showdown(&newGame);
        }

        printf("\n--- Chip Counts ---\n");
        int opponents_with_chips = 0;
        for (int i = 0; i < config.num_of_players; i++) {
          if (newGame.players[i].chips > 0) {
            printf("%s: %d chips\n", newGame.players[i].name,
                   newGame.players[i].chips);
            if (i != 0) {
              opponents_with_chips++;
            }
          } else {
            printf("%s: 0 chips (Busted)\n", newGame.players[i].name);
          }
        }

        if (newGame.players[0].chips <= 0) {
          printf("\n[GAME OVER] You ran out of chips! Better luck next time.\n");
          break;
        }

        if (opponents_with_chips == 0) {
          printf("\n[CONGRATULATIONS] You eliminated all opponents and won the tournament!\n");
          break;
        }

        printf("\n[Press ENTER to play next hand or 'q' to quit]\n");
        if (!fgets(input, sizeof(input), stdin))
          break;
        if (input[0] == 'q' || input[0] == 'Q') {
          printf("Leaving table with %d chips. Thanks for playing!\n",
                 newGame.players[0].chips);
          break;
        }

        startNewHand(&newGame);
        hand_number++;
      }
      break;
    } else if (input[0] == 'q' || input[0] == 'Q') {
      printf("User Quitted\n");
      exit(0);
    }
  }
  return 0;
}