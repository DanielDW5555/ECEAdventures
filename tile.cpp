#include <iostream>
#include "include.h"
using namespace std;

// Returns the tiles string
string Tile::getTile()
{
        return tile;
}

void Tile::setState(char wantedState)
{
	state = wantedState;
}

// Sets a tile to be another string
void Tile::setTile(string tileType)
{
        tile = tileType;
}

