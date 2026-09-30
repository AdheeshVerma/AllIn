# AllIn
**AllIn** is a terminal-based Texas Hold'em poker engine written in ISO C17 (`-std=c17`). The program implements a single-table Texas Hold'em game supporting 2 to 9 players (1 human player and 1 to 8 AI-controlled opponents).

## Core Capabilities Currently Implemented
1. **Interactive Configuration**: Command-line terminal setup allowing the user to select the number of opponents (2 to 8, or randomized 3 to 5) and one of three blind tiers (`Casual`, `High Stakes`, `NO MERCY`).
2. **Standard 52-Card Deck Management**: Card representation with 4 suits and 13 ranks, Fisher-Yates uniform shuffle algorithm, card dealing, and burn cards before the flop, turn, and river.
3. **Turn and Action Rotation**: Rotation through dealer button, small blind posting, big blind posting, under-the-gun (UTG) first-to-act, and post-flop dealer-relative rotations.
4. **Complete Betting Loop**: Action choices for Check, Call, Raise (with min-raise and max-raise constraints), and Fold; all-in tracking; action reopening upon raise; and early pot award if all opponents fold.
5. **Basic AI Decision Engine**: Rule-based AI opponents evaluating `to_call`, chip count, and random betting probabilities.
6. **Texas Hold'em Hand Evaluator**: Evaluation of any 5-card combination across all 10 standard poker hand rankings (High Card to Royal Flush), plus a 7-card evaluator that enumerates all $\binom{7}{5} = 21$ combinations to find the player's optimal 5-card hand and break ties using descending kicker arrays.
7. **Showdown & Pot Resolution**: Card reveals, best-hand comparisons, single winner pot collection, and equal split-pot division on ties.

---

## Specifications
1. **Language**: Written in C17 (`-std=c17`) with zero external dependencies.
2. **Players**: 2 to 9 players (1 human player vs. 1 to 8 AI opponents).
3. **Game Rules**: Standard No-Limit Texas Hold'em with blinds, betting rounds, and all-in support.
4. **Deck**: Standard 52-card deck using Fisher-Yates shuffling and burn cards.
5. **Hand Evaluation**: Best 5 of 7 cards evaluated with standard hand ranks and kickers.

---

# Design
```text
AllIn/
├── Makefile                     # Build instructions (gcc, C17, flags, targets)
├── .gitignore                   # Ignores build/ and vault/
├── README.md                    # Project readme
├── build/                       # Compilation output (object files and executable)
│   ├── allin                    # Final executable binary
│   ├── card.o                   # Compiled card module
│   ├── deck.o                   # Compiled deck module
│   ├── game.o                   # Compiled core game loop & betting engine
│   ├── gameInit.o               # Compiled game initialization
│   ├── gameSetup.o              # Compiled interactive user config
│   ├── handEvaluator.o          # Compiled poker ranking & hand evaluation
│   └── main.o                   # Compiled entry point
├── include/                     # Public header files (.h)
│   ├── card.h                   # Card, Suit, Rank declarations
│   ├── deck.h                   # Deck structure and deck operations
│   ├── gameConfig.h             # Blind enum, BlindInfo, GameConfig declarations
│   ├── game.h                   # Game, Phase enum, table coordination headers
│   ├── gameInit.h               # Game state initialization signature
│   ├── gameSetup.h              # Interactive terminal setup signature
│   ├── handEvaluator.h          # HandRankType enum, HandValue, evaluator signatures
│   ├── player.h                 # Player structure declaration
│   └── table.h                  # Table structure declaration
├── src/                         # Implementation source files (.c)
│   ├── card.c                   # Card rendering implementation
│   ├── deck.c                   # Deck initialization, shuffle, and deal logic
│   ├── game.c                   # Betting engine, turn rotation, phases, showdown
│   ├── gameInit.c               # Default game state population and player setup
│   ├── gameSetup.c              # Terminal menus for blind and opponent selection
│   ├── handEvaluator.c          # Combinatorics, rank counting, tie-breaker logic
│   └── main.c                   # Main program entry, banner, and round loop
└── vault/                       # Obsidian documentation vault (unmonitored by git)
    └── AllIn/                   # Developer design notes and architectural specs
```
---
# How to play

```
git clone https://github.com/AdheeshVerma/AllIn
cd AllIn
make run
```