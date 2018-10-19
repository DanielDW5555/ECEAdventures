#include <iostream>
#include "include.h"
using namespace std;

// Returns the tiles string
string Tile::getTile()
{
        return tile;
}

// Sets a tile to be another string
void Tile::setTile(string tileType)
{
        tile = tileType;
}

