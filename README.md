# Pokemon Battle Game

## Overview
The Pokemon Battle Game is a text-based simulation where players can battle Pokemon, level them up, and catch new ones. Players can choose from three starter Pokemon and engage in battles against enemy Pokemon with various attack and defense options.

## Features
- Choose from three starter Pokemon: Charmander, Mudkip, and Bulbasaur.
- Engage in battles with enemy Pokemon.
- Perform different types of attacks including special and defensive attacks.
- Catch enemy Pokemon if their HP is low.
- Level up your Pokemon and update their stats.
- Heal all your Pokemon to reset their stats.

## Setup
To run the Pokemon Battle Game, you need to have a C++ compiler installed on your system.

1. Clone the repository or download the source code.
2. Navigate to the directory containing the source code.
3. Compile the source code using your C++ compiler. For example:
    ```bash
    g++ -o PokemonBattleGame main.cpp
    ```
4. Run the compiled program:
    ```bash
    ./PokemonBattleGame
    ```

## How to Play
1. **Start the Game**:
    - Enter your name when prompted.

2. **Choose Your Starter Pokemon**:
    - Select from Charmander, Mudkip, and Bulbasaur by entering the corresponding number.

3. **Battle Mechanics**:
    - You can attack, use healing items, perform special or defensive attacks, or attempt to catch the enemy Pokemon.
    - The game will prompt you for your action during your turn in the battle.

4. **Level Up**:
    - Gain XP by defeating enemy Pokemon. Level up when enough XP is gained, and your Pokemon's stats will be updated.

5. **Heal All Pokemon**:
    - Use the `healAllPokemon` function to reset all stats for your Pokemon in the inventory.

## Classes and Methods
### Pokemon Class
- **Attributes**: `name`, `hp`, `maxHP`, `attack`, `level`, `xp`, `maxXP`.
- **Methods**: `getName()`, `getLevel()`, `resetStats()`, `updateStats()`, `getWeakness()`, `getStrength()`, `getAttack()`, `getType()`, `getHP()`, `setHP()`, `getXP()`, `setXP()`, `setLevel()`.

### FireType, WaterType, GrassType Classes
- Derived from the `Pokemon` class with specific attributes for each type.

### User Class
- **Attributes**: `name`, `inventory`, `currPokemon`, `selectedPokemon`, `maxPokemon`.
- **Methods**: `getName()`, `addPokemon()`, `displayAllPokemon()`, `setSelectedPokemon()`, `getSelectedPokemon()`, `getCurrPokemon()`, `battle()`, `healAllPokemon()`.

