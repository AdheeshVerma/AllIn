#ifndef ALLIN_GAMECONFIG_H
#define ALLIN_GAMECONFIG_H
typedef enum
{
    CASUAL_10_20 = 1,
    HIGH_STAKES_50_100,
    NO_MERCY_500_1000,
    BLIND_COUNT
} Blind;
typedef struct
{
    Blind level;
    const char *name;
    int small_blind;
    int big_blind;
} BlindInfo;
typedef struct
{
    int num_of_players;
    Blind blind_level;
} GameConfig;
extern const BlindInfo blind_table[BLIND_COUNT - 1];
#endif
