#include <iostream>
#include "include.h"
using namespace std;

void Entity::checkDeath()
{
	if(health <= 0)	isDead = true;
}

int Entity::damageStats()
{
	return strength;
}
