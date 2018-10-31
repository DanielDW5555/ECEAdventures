#include <iostream>
#include "include.h"
using namespace std;

// Constructors
// Entity with its values
Entity::Entity(string icon, string name, string description, int health, int strength, int defense, int range, int intelligence) : icon(icon), name(name), description(description), health(health), strength(strength), defense(defense), range(range), intelligence(intelligence)
{
}
// Entity with no values declared
Entity::Entity() : name("Unknown"), description("Unknown"), health(1), strength(1), defense(1), range(1), intelligence(0)
{
}

// Calculates the chalange rating of the entity
int Entity::CR()
{
	return health + strength + defense;
}

void Entity::checkDeath()
{
	if(health <= 0)	isDead = true;
}

int Entity::damageStats()
{
	return strength;
}
