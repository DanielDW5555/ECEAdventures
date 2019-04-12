#include <iostream>
#include "include.h"
using namespace std;

// Constructor
/*
Player::Player(int lvl, int hp, int maxHp, int str, int def, int rang, int xp) : level(lvl), health(hp), maxHealth(maxHp), strength(str), defense(def), range(rang), exp(xp)
{
}
*/

int Player::damageStats()
{
        return strength;
}

string Player::getIcon()
{
        return icon;
}

int Player::CR()
{
        return health + strength + defense;
}

int Player::expToNextLevel()
{
        return CR() * 2;
}

int Player::checkExp()
{
        if (exp >= expToNextLevel())
        {
                cout << "Level up!" << endl;
                int numberOfStatIncreases = rand() % (CR() / 2);

                for (int i = 0; i < numberOfStatIncreases; i++)
                {
                        int typeToLevel = rand() % 3;

                        if (typeToLevel == 1)
                        {
                                maxHealth += 1;
                        }
                        if (typeToLevel == 2)
                        {
                                strength += 1;
                        }
                        if (typeToLevel == 3)
                        {
                                defense += 1;
                        }
                }
                health = maxHealth;
                exp = 0;
        }

        return 0;
}