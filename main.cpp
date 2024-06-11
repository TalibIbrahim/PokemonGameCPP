#include <iostream>
#include <cmath>
#include <random>

using namespace std;

int getRandomNumber(int min, int max)
{
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(min, max);
    return distr(eng);
}

class Pokemon
{
protected:
    string name;
    int hp;
    int maxHP;
    int attack;
    int level;
    int xp;
    int maxXP = 100;

public:
    string getName()
    {
        return name;
    }
    int getLevel()
    {
        return level;
    }

    void resetStats()
    {
        // Reset stats based on level
        hp = maxHP;
        attack = round(attack * pow(1.25, level - 1));
    }

    // UPDATE STATS RUNS WHEN USER LEVELS UP. STATS CHANGE ACCORDING TO LEVEL.
    void updateStats()
    {
        hp = round(hp * pow(1.25, level - 1));
        maxHP = hp;
        attack = round(attack * pow(1.25, level - 1));
    }

    virtual string getWeakness() = 0;
    virtual string getStrength() = 0;
    virtual int getAttack() = 0;

    virtual string getType() = 0;
    virtual int getHP() = 0;
    virtual void setHP(int hp) = 0;
    virtual int getXP() = 0;
    virtual void setXP(int xp) = 0;
    virtual void setLevel(int level) = 0;

    // Pure virtual functions to make the class abstract. This makes us able to use these functions in the derived classes by calling it from Pokemon class directly.
};

class FireType : public Pokemon
{
private:
    string weakness = "Water";
    string strength = "Grass";

public:
    FireType(string name, int hp, int attack, int level)
    {
        this->name = name;
        this->hp = hp;
        maxHP = hp;
        this->attack = attack;

        this->level = level;
        xp = 0;
    }

    string getWeakness()
    {
        return weakness;
    }
    string getStrength()
    {
        return strength;
    }
    int getAttack()
    {
        return attack;
    }

    int getHP()
    {
        return hp;
    }
    string getType()
    {
        return "Fire";
    }
    void setHP(int hp)
    {
        this->hp = hp;
    }
    int getXP()
    {
        return xp;
    }
    void setXP(int xp)
    {
        this->xp = xp;
    }
    void setLevel(int level)
    {
        this->level = level;
    }
};

class WaterType : public Pokemon
{
private:
    string weakness = "Grass";
    string strength = "Fire";

public:
    WaterType(string name, int hp, int attack, int level)
    {
        this->name = name;
        this->hp = hp;
        maxHP = hp;

        this->attack = attack;
        this->level = level;
        xp = 0;
    }
    string getWeakness()
    {
        return weakness;
    }
    string getStrength()
    {
        return strength;
    }
    int getAttack()
    {
        return attack;
    }

    int getHP()
    {
        return hp;
    }
    string getType()
    {
        return "Water";
    }
    void setHP(int hp)
    {
        this->hp = hp;
    }
    int getXP()
    {
        return xp;
    }
    void setXP(int xp)
    {
        this->xp = xp;
    }
    void setLevel(int level)
    {
        this->level = level;
    }
};

class GrassType : public Pokemon
{
private:
    string weakness = "Fire";
    string strength = "Water";

public:
    GrassType(string name, int hp, int attack, int level)
    {
        this->name = name;
        this->hp = hp;
        maxHP = hp;

        this->attack = attack;
        this->level = level;
        xp = 0;
    }
    string getWeakness()
    {
        return weakness;
    }
    string getStrength()
    {
        return strength;
    }
    int getAttack()
    {
        return attack;
    }

    int getHP()
    {
        return hp;
    }
    string getType()
    {
        return "Grass";
    }
    void setHP(int hp)
    {
        this->hp = hp;
    }
    int getXP()
    {
        return xp;
    }
    void setXP(int xp)
    {
        this->xp = xp;
    }
    void setLevel(int level)
    {
        this->level = level;
    }
};

class User
{
private:
    string name;

    Pokemon *inventory[3];
    int currPokemon;
    int selectedPokemon;
    int maxPokemon = 3;

public:
    User(string name)
    {
        this->name = name;

        currPokemon = 0;
    }

    string getName()
    {
        return name;
    }

    void addPokemon(Pokemon &p)
    {
        if (currPokemon < maxPokemon)
        {
            inventory[currPokemon] = &p;
            currPokemon++;
            cout << "Added Pokemon to your Inventory" << endl;
            cout << "Current Pokemon: " << currPokemon << endl;
        }
        else
        {
            cout << "Inventory is full" << endl;
        }
    }
    void displayAllPokemon()
    {
        for (int i = 0; i < currPokemon; i++)
        {
            cout << "Pokemon " << i + 1 << ": " << inventory[i]->getName() << " | Level: " << inventory[i]->getLevel() << " | Health: " << inventory[i]->getHP() << " | Attack: " << inventory[i]->getAttack() << " | Index: " << i << endl;
        }
    }

    void setSelectedPokemon(int selectedPokemon)
    {
        this->selectedPokemon = selectedPokemon;
    }

    Pokemon *getSelectedPokemon()
    {
        return inventory[selectedPokemon];
    }
    int getCurrPokemon()
    {
        return currPokemon;
    }

    // MAIN BATTLE FUNCTION:

    void battle(Pokemon &userPokemon, Pokemon &enemyPokemon)
    {
        int option = 0;
        float enemyAttackMultiplier = 1;
        float userAttackMultiplier = 1;
        bool battleOver = false;

        // ATTACK MULTIPLIERS:

        if (userPokemon.getWeakness() == enemyPokemon.getType())
        {
            enemyAttackMultiplier = 1.1;
            userAttackMultiplier = 0.9;
        }
        else if (userPokemon.getStrength() == enemyPokemon.getType())
        {
            userAttackMultiplier = 1.1;
            enemyAttackMultiplier = 0.9;
        }
        else
        {
            userAttackMultiplier = 1;
            enemyAttackMultiplier = 1;
        }

        int damageCalc = 0;
        while (!battleOver)
        {
            cout << "----------------------------------------------------------------------------------------------------" << endl;
            cout << "Enter 1 to attack, 2 to use healing, 3 to use special attack, 4 for defensive attack, 5 for catching enemy Pokemon" << endl;
            cin >> option;

            switch (option)
            {
            case 1:

                damageCalc = userAttackMultiplier * userPokemon.getAttack();
                if (damageCalc < 0)
                {

                    damageCalc = 0;
                } // Prevent negative damage (healing attacks

                enemyPokemon.setHP(enemyPokemon.getHP() - damageCalc);

                cout << userPokemon.getName() << " attacks " << enemyPokemon.getName() << " for " << damageCalc << " damage. Enemy HP left: " << enemyPokemon.getHP() << endl;
                cout << endl;

                //    CHECK ENEMY POKEMON HP
                if (enemyPokemon.getHP() <= 0)
                {
                    cout << enemyPokemon.getName() << " fainted!" << endl;
                    cout << "XP gained: " << enemyPokemon.getLevel() * 10 << endl;
                    userPokemon.setXP(userPokemon.getXP() + enemyPokemon.getLevel() * 10);
                    if (userPokemon.getXP() >= userPokemon.getLevel() * 100)
                    {
                        userPokemon.setXP(userPokemon.getXP() - userPokemon.getLevel() * 100);
                        userPokemon.setLevel(userPokemon.getLevel() + 1);
                        cout << "Level up! New level: " << userPokemon.getLevel() << endl;
                        userPokemon.resetStats();
                        userPokemon.updateStats();
                        // LEVELS UP A POKEMON AND RESETS STATS ACCORDINGLY
                    }

                    cout << endl;

                    battleOver = true;
                }

                break;
            case 2:
                cout << userPokemon.getName() << " uses a healing item." << endl;
                cout << endl;

                userPokemon.setHP(userPokemon.getHP() + 15);
                cout << "Your HP: " << userPokemon.getHP() << endl;
                break;
            case 3:
                cout << userPokemon.getName() << " uses a special attack." << endl;
                cout << endl;

                damageCalc = userAttackMultiplier * userPokemon.getAttack() * 1.5;

                if (damageCalc < 0)
                {

                    damageCalc = 0;
                } // Prevent negative damage (healing attacks

                enemyPokemon.setHP(enemyPokemon.getHP() - damageCalc);
                cout << userPokemon.getName() << " attacks " << enemyPokemon.getName() << " for " << damageCalc << " damage. Enemy HP left: " << enemyPokemon.getHP() << endl;
                cout << endl;

                //    CHECK ENEMY POKEMON HP
                if (enemyPokemon.getHP() <= 0)
                {
                    cout << enemyPokemon.getName() << " fainted!" << endl;
                    cout << "XP gained: " << enemyPokemon.getLevel() * 10 << endl;
                    userPokemon.setXP(userPokemon.getXP() + enemyPokemon.getLevel() * 10);
                    if (userPokemon.getXP() >= userPokemon.getLevel() * 100)
                    {
                        userPokemon.setXP(userPokemon.getXP() - userPokemon.getLevel() * 100);
                        userPokemon.setLevel(userPokemon.getLevel() + 1);
                        cout << "Level up! New level: " << userPokemon.getLevel() << endl;
                        userPokemon.resetStats();
                        userPokemon.updateStats();
                        // LEVELS UP A POKEMON AND RESETS STATS ACCORDINGLY
                    }
                    cout << endl;

                    battleOver = true;
                }

                break;
            case 4:
                cout << userPokemon.getName() << " uses a defensive attack." << endl;
                cout << endl;

                // In this attack, pokemon steals 5 * userAttackMultiplier of the enemy's HP
                damageCalc = 5 * userAttackMultiplier;

                if (damageCalc < 0)
                {
                    damageCalc = 0;
                } // Prevent negative damage (healing attacks

                userPokemon.setHP(userPokemon.getHP() + damageCalc);
                enemyPokemon.setHP(enemyPokemon.getHP() - damageCalc);
                cout << userPokemon.getName() << " steals " << damageCalc << " HP from " << enemyPokemon.getName() << ". Enemy HP left: " << enemyPokemon.getHP() << endl;

                //    CHECK ENEMY POKEMON HP
                if (enemyPokemon.getHP() <= 0)
                {
                    cout << enemyPokemon.getName() << " fainted!" << endl;
                    cout << "XP gained: " << enemyPokemon.getLevel() * 10 << endl;
                    userPokemon.setXP(userPokemon.getXP() + enemyPokemon.getLevel() * 10);
                    if (userPokemon.getXP() >= userPokemon.getLevel() * 100)
                    {
                        userPokemon.setXP(userPokemon.getXP() - userPokemon.getLevel() * 100);
                        userPokemon.setLevel(userPokemon.getLevel() + 1);
                        cout << "Level up! New level: " << userPokemon.getLevel() << endl;
                        userPokemon.resetStats();
                        userPokemon.updateStats();
                        // LEVELS UP A POKEMON AND RESETS STATS ACCORDINGLY
                    }
                    cout << endl;

                    battleOver = true;
                }
                break;

            case 5:
                cout << "Catching enemy Pokemon..." << endl;
                if (currPokemon < maxPokemon)
                {
                    if (enemyPokemon.getHP() <= 15)
                    {
                        cout << "Enemy Pokemon HP: " << enemyPokemon.getHP() << endl;
                        cout << "You caught " << enemyPokemon.getName() << "!" << endl;
                        addPokemon(enemyPokemon);
                        cout << endl;
                        battleOver = true;
                    }
                    else
                    {
                        cout << "Enemy Pokemon HP: " << enemyPokemon.getHP() << endl;
                        cout << "Unable to catch a healthy Pokemon" << endl;
                        cout << endl;
                    }
                }
                else
                {
                    cout << "Inventory is full. Cannot catch enemy Pokemon." << endl;
                    cout << endl;
                }
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
            }

            // -----------------------------------------------------------
            // AI ENEMY ATTACK TURN:

            if (battleOver)
            {
                break;
            }

            int action = getRandomNumber(0, 1);

            // This makes it so that enemy will either heal or attack based if its health is below 50. Basically a 50% chance of healing or attacking when below certain health.

            if (enemyPokemon.getHP() < 50 && action == 0)
            {
                cout << enemyPokemon.getName() << " uses a healing item." << endl;
                cout << endl;

                enemyPokemon.setHP(enemyPokemon.getHP() + 15);
                cout << "Enemy HP: " << enemyPokemon.getHP() << endl;
                cout << endl;
            }
            else
            {

                int enemyOption = getRandomNumber(1, 4);

                switch (enemyOption)
                {
                case 1:
                    cout << enemyPokemon.getName() << " attacks!" << endl;
                    cout << endl;

                    damageCalc = enemyAttackMultiplier * enemyPokemon.getAttack();

                    if (damageCalc < 0)
                    {

                        damageCalc = 0;
                    } // Prevent negative damage (healing attacks

                    userPokemon.setHP(userPokemon.getHP() - damageCalc);
                    cout << enemyPokemon.getName() << " attacks " << userPokemon.getName() << " for " << damageCalc << " damage. Your HP left: " << userPokemon.getHP() << endl;
                    cout << endl;

                    if (userPokemon.getHP() <= 0)
                    {
                        cout << "You fainted!" << endl;
                        battleOver = true;
                    }
                    break;
                case 2:
                    cout << enemyPokemon.getName() << " uses a healing item." << endl;
                    cout << "Enemy HP: " << enemyPokemon.getHP() << endl;

                    cout << endl;

                    enemyPokemon.setHP(enemyPokemon.getHP() + 15);
                    break;
                case 3:
                    cout << enemyPokemon.getName() << " uses a special attack." << endl;
                    cout << endl;

                    damageCalc = enemyAttackMultiplier * enemyPokemon.getAttack() * 1.5;

                    if (damageCalc < 0)
                    {

                        damageCalc = 0;
                    } // Prevent negative damage (healing attacks

                    userPokemon.setHP(userPokemon.getHP() - damageCalc);
                    cout << enemyPokemon.getName() << " attacks " << userPokemon.getName() << " for " << damageCalc << " damage. Your HP left: " << userPokemon.getHP() << endl;
                    cout << endl;

                    if (userPokemon.getHP() <= 0)
                    {
                        cout << "You fainted!" << endl;
                        battleOver = true;
                    }
                    break;

                case 4:
                    cout << enemyPokemon.getName() << " uses a defensive attack." << endl;
                    cout << endl;

                    // In this attack, pokemon steals 5 * enemyAttackMultiplier of the user's HP
                    damageCalc = 5 * enemyAttackMultiplier;

                    if (damageCalc < 0)
                    {
                        damageCalc = 0;
                    } // Prevent negative damage (healing attacks

                    enemyPokemon.setHP(enemyPokemon.getHP() + damageCalc);
                    userPokemon.setHP(userPokemon.getHP() - damageCalc);

                    cout << enemyPokemon.getName() << " steals " << damageCalc << " HP from you. Your HP left: " << userPokemon.getHP() << endl;

                    if (userPokemon.getHP() <= 0)
                    {
                        cout << "You fainted!" << endl;
                        battleOver = true;
                    }
                    break;
                }
            }
        }
    }
    void healAllPokemon()
    {
        // Resets all stats for all pokemon in the inventory
        for (int i = 0; i < currPokemon; i++)
        {
            inventory[i]->resetStats();
        }
        cout << "All Pokemon healed!" << endl;
        cout << endl;
    }
};

int main()
{
    // USER CREATION:
    cout << "Enter your name: " << endl;
    string name;
    cin >> name;
    User player(name);
    cout << endl;
    cout << "Welcome, " << player.getName() << "!" << endl;
    cout << endl;

    // 3 starting POKEMON to pick from:

    FireType charmander("Charmander", 130, 60, 1);
    WaterType mudkip("Mudkip", 160, 50, 1);
    GrassType bukbasaur("Bulbasaur", 170, 40, 1);
    int pick;

// USER PICKS A POKEMON:
pick:
    cout << "Select a Pokemon: " << endl;
    cout << "1. Charmander (FIRE TYPE)" << endl;
    cout << "2. Mudkip (WATER TYPE)" << endl;
    cout << "3. Bulbasaur (GRASS TYPE)" << endl;
    cin >> pick;
    if (pick == 1)
    {
        cout << "You picked Charmander!" << endl;
        player.addPokemon(charmander);
        player.setSelectedPokemon(0);
        cout << endl;
    }
    else if (pick == 2)
    {
        cout << "You picked Mudkip!" << endl;
        player.addPokemon(mudkip);
        player.setSelectedPokemon(0);
        cout << endl;
    }
    else if (pick == 3)
    {
        cout << "You picked Bulbasaur!" << endl;
        player.addPokemon(bukbasaur);
        player.setSelectedPokemon(0);
        cout << endl;
    }
    else
    {
        cout << "Invalid choice. Please pick again." << endl;
        goto pick;
    }

    // AI POKEMON ENEMY (ARRAY) CREATION:
    Pokemon *enemyPokemon[15] = {
        // Level 1:
        new FireType("Charmander", 130, 60, 1),
        new WaterType("Mudkip", 160, 50, 1),
        new GrassType("Bulbasaur", 170, 40, 1),

        // Level 2:
        new FireType("Charmander", 163, 75, 2),
        new WaterType("Mudkip", 200, 63, 2),
        new GrassType("Bulbasaur", 213, 50, 2),

        // Level 3:
        new FireType("Charmander", 203, 94, 3),
        new WaterType("Mudkip", 250, 78, 3),
        new GrassType("Bulbasaur", 267, 63, 3),

        // Level 4:
        new FireType("Charmander", 254, 117, 4),
        new WaterType("Mudkip", 313, 98, 4),
        new GrassType("Bulbasaur", 333, 78, 4),

        // Level 5:
        new FireType("Charmander", 317, 146, 5),
        new WaterType("Mudkip", 391, 122, 5),
        new GrassType("Bulbasaur", 417, 98, 5)};

    cout << endl;

    // Now, the user can start battling with the enemy pokemons. This has no multiplayer feature. All AI controlled enemies.
    int choice = 0;

    while (choice != 6)
    {

        cout << "Choose one of these choices:" << endl;
        cout << "1. Pick Main Pokemon" << endl;
        cout << "2. Display Main Pokemon" << endl;
        cout << "3. Heal all Pokemon" << endl;
        cout << "4. Display all Pokemon" << endl;
        cout << "5. Battle" << endl;
        cout << "6. Exit" << endl;
        cout << endl;

        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            int selection;
            cout << "Select a Pokemon (index): " << endl;
            player.displayAllPokemon();
            cin >> selection;
            if (selection < player.getCurrPokemon() && selection >= 0)

            {
                player.setSelectedPokemon(selection);
                cout << "Selected Pokemon: " << player.getSelectedPokemon()->getName() << endl;
                cout << endl;
            }
            else
            {
                cout << "Invalid choice." << endl;
                cout << endl;
            }

            break;
        case 2:
            cout << "Selected Pokemon: " << player.getSelectedPokemon()->getName() << endl;
            cout << endl;

            break;
        case 3:
            cout << "Healing all Pokemon" << endl;
            player.healAllPokemon();
            cout << endl;

            break;
        case 4:
            cout << "Displaying all Pokemon" << endl;
            player.displayAllPokemon();
            cout << endl;

            break;
        case 5:
            int enemyPokemonPick_MIN, enemyPokemonPick_MAX, enemyPokemonIndex;
            cout << "Finding a battle..." << endl;
            cout << endl;

            if (player.getSelectedPokemon()->getLevel() == 1)
            {
                enemyPokemonPick_MIN = 0;
                enemyPokemonPick_MAX = 2;
                enemyPokemonIndex = getRandomNumber(enemyPokemonPick_MIN, enemyPokemonPick_MAX);
            }
            else if (player.getSelectedPokemon()->getLevel() == 2)
            {
                enemyPokemonPick_MIN = 3;
                enemyPokemonPick_MAX = 5;
                enemyPokemonIndex = getRandomNumber(enemyPokemonPick_MIN, enemyPokemonPick_MAX);
            }
            else if (player.getSelectedPokemon()->getLevel() == 3)
            {
                enemyPokemonPick_MIN = 6;
                enemyPokemonPick_MAX = 8;
                enemyPokemonIndex = getRandomNumber(enemyPokemonPick_MIN, enemyPokemonPick_MAX);
            }
            else if (player.getSelectedPokemon()->getLevel() == 4)
            {
                enemyPokemonPick_MIN = 9;
                enemyPokemonPick_MAX = 11;
                enemyPokemonIndex = getRandomNumber(enemyPokemonPick_MIN, enemyPokemonPick_MAX);
            }
            else if (player.getSelectedPokemon()->getLevel() == 5)
            {
                enemyPokemonPick_MIN = 12;
                enemyPokemonPick_MAX = 14;
                enemyPokemonIndex = getRandomNumber(enemyPokemonPick_MIN, enemyPokemonPick_MAX);
            }
            cout << "Found an enemy Pokemon!" << endl;
            cout << endl;

            cout << "Enemy Pokemon: " << enemyPokemon[enemyPokemonIndex]->getName() << " | Level: " << enemyPokemon[enemyPokemonIndex]->getLevel() << endl;
            cout << endl;

            player.battle(*player.getSelectedPokemon(), *enemyPokemon[enemyPokemonIndex]);
            enemyPokemon[enemyPokemonIndex]->resetStats();
            cout << endl;

            break;
        case 6:
            cout << "Exiting..." << endl;
            cout << endl;

            break;
        default:
            cout << "Invalid choice." << endl;
            cout << endl;

            break;
        }
    }

    return 0;
}
