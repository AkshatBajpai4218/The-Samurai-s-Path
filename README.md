# The Samurai's Path — game.cpp

A compact, single-file C++ text adventure where you play a wandering samurai. The game mixes short-choice encounters, randomized combat, and simple resource management (HP, potions, focus). It's designed to run from the terminal and compile with a standard g++ toolchain.

## Features

- Interactive, turn-based combat with randomized damage.
- Player resources: HP, Potions (heal + temporary damage buff), Focus (fuel for special strikes).
- Buffs and debuffs:
  - `playerBuffTurns` and `playerDamageBonus` increase player damage for a few attacks (from potions or focus).
  - `enemyBuffTurns` and `enemyDamageBonus` make enemies more aggressive after certain player actions.
  - `potionResistTurns` caps the damage of the next enemy hit to 4 when a potion is used.
- Multiple situations to explore: Forest (early fight), Village (thieves), Marketplace, Swamp (environmental hazard), Temple (riddle), Mountain pass (ambush), and a multi-phase Final Castle duel.
- Honor tracking which influences the ending.

## Quick compile & run (Windows PowerShell)

The game is a single C++ file that requires a C++17-capable compiler (g++/MinGW, or equivalent).

```powershell
# Compile
g++ "d:\Kuchh bhi\Samurai\game.cpp" -O2 -std=c++17 -o "d:\Kuchh bhi\Samurai\game.exe"

# Run (interactive)
& "d:\Kuchh bhi\Samurai\game.exe"
```

Notes:
- The program reads simple numeric choices from standard input and a short text answer at the temple riddle.
- If the compiled executable is locked by your system (e.g., still running), compile to a different name (e.g. `game_fixed.exe`).

## How to play (summary)

- Enter your samurai's name when prompted.
- Choose numbered options (1, 2, 3, ...) for each prompt.
- Manage your potions and focus:
  - Drinking a potion heals 20 HP (clamped to your max HP) and grants a temporary damage buff for your next two attacks. It also grants a one-time resistance that caps the *next* enemy hit at 4 damage.
  - A special strike consumes 1 focus and deals heavy damage while giving a temporary strong buff to your next attacks, but can make enemies more aggressive for a short period.
- Watch your HP; many encounters (especially the swamp and the final duel) are dangerous.
- Your choices affect `honor` — this value determines which ending you receive.

## Internal mechanics (for maintainers)

Key variables in `game.cpp`:

- `hp`, `maxHP`: player's health.
- `potions`: number of potions available.
- `focus`: resource for special strikes.
- `playerBuffTurns`, `playerDamageBonus`: player damage buff counters and value.
- `enemyBuffTurns`, `enemyDamageBonus`: temporary enemy damage buff.
- `potionResistTurns`: when > 0 the next enemy hit is capped to 4 damage and then the flag is cleared.

Combat uses `randBetween(a,b)` to generate randomized damage values.

## Suggested improvements / TODO

- Implement a multi-step `defend` mechanic for the final boss (currently defend simply recovers a small amount of HP).
- Add a safer `readIntInRange()` helper to avoid `cin`/`getline` mixing issues, and a status line helper (these were prototyped in a separate `final_game.cpp`).
- Add ANSI colorized output (like a `final_game.cpp` variant) for better readability.
- Add unit tests or a scripted input harness to exercise edge cases (low HP, no potions/focus, repeated buffs).

## License & attribution

This file is provided without an explicit license. If you plan to publish or reuse it, consider adding a license (MIT/Apache2) and keeping a note of the original author.

---

If you want, I can:

- Add the defend-count mechanic you requested to `game.cpp` (three-step defend behavior), apply it, recompile, and run a quick smoke test.
- Or port the colored status output from `final_game.cpp` into this file.

Tell me which change to make next and I'll implement it.
