#ifndef ALLIN_GAMECONFIG_H
#define ALLIN_GAMECONFIG_H
typedef enum
{
    CASUAL_10_20 = 1,
    HIGH_STAKES_50_100,
    NO_MERCY_500_1000,
} Blind;
typedef struct
{
    int num_of_players;
    Blind blind_level;
    int small_blind;
    int big_blind;

} GameConfig;
#endif
