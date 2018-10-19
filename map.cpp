#include <iostream>
#include "include.h"
using namespace std;

// Generates a map based on the parameters passed in
void Map::createMap(const int numberOfRooms, const int maxSize, const int minSize)
{
        srand(time(NULL));

        for(int z = 0; z < numberOfRooms; z ++)
        {
                // Creates random rooms with random size and locations given by the screens size and maximun/minimum room specifications
                int x = rand() % width;
                int y = rand() % height;
                int rWidth = rand() % maxSize;
                int rHeight = rand() % maxSize;
                
                //Checks the room width and height to make sure its biger than minSize
                while(rWidth < minSize) rWidth = rand() % maxSize;
                while(rHeight < minSize) rHeight = rand() % maxSize;
                
                //Once rooms are propper size, check to see if the room fits on the map
                while( (x+rWidth) >= width-1) x = rand() % width;
                while( (y+rHeight) >= height-1) y = rand() % height;
                cout << "X:" << x << " Y:" << y << " Width:" << rWidth << " Height:" << rHeight << endl;
                
                // Setting tiles to be the shapes of the rooms at random x and y locations
                for(int j = 0; j < height; j ++)
                {
                        for(int i = 0; i < width; i ++)
                        {
                                if(i >= x && i <= (x+rWidth) && j >= y && j <= (y+rHeight)) // If loop is at the correct cords to make a room, generate
                                        t[i][j].setTile("r");
                        }
                }

        }
}

// Takes the strings/characters that each entity contains and stiles it to a pleasing format
void Map::render()
{
        for(int j = 0; j < height; j ++)
        {
                for(int i = 0; i < width; i ++)
                {
                        if(p.x == i && p.y == j) cout << p.getIcon(); // prints player
                        else if(t[i][j].getTile() == " ") cout << "▓"; // Prints an empty space to be a wall
                        else if(t[i][j].getTile() == "r") cout << " "; // Prints a room tile as an empty tile
                }
                cout << endl;
        }
}

// Spawns the player on a random room tile
void Map::spawnPlayer()
{
        int randX = rand() % width;
        int randY = rand() % height;
        while(t[randX][randY].getTile() != "r") randX = rand() % width;
        while(t[randX][randY].getTile() != "r") randY = rand() % height;
        p.x = randX;
        p.y = randY;
        cout << "player x:" << randX << " player y:" << randY << endl;
}

// This is called whenever an entity wants to move on the map
bool Map::moveRequest(int x, int y, char direction)
{
	if(direction == 'd' && t[x+1][y].getTile() == "r") return 1;
	else if(direction == 'a' && t[x-1][y].getTile() == "r") return 1;
	else if(direction == 'w' && t[x][y-1].getTile() == "r") return 1;
	else if(direction == 's' && t[x][y+1].getTile() == "r") return 1;
	else return 0;
}

// Moves the player depending on the response to moveRequest
void Map::movePlayer()
{
	char d;
        cin >> d;
        if(moveRequest(p.x, p.y, d))    // Checks to see if there is anything in players way before moving the player
        {
                if(d == 'w') p.y--;
                else if(d == 's') p.y++;
                else if(d == 'a') p.x--;
                else if(d == 'd') p.x++;
        }
        else
        {
                cout << "Somthing is in the way!" << endl;
        }

}

void Map::update()
{
	while(true)
	{
	movePlayer();
	render();
	}
}

// Creates a map
void Map::init()
{
        const int numberOfRooms = 20;
        const int maxSize = 7;
        const int minSize = 3;

        createMap(numberOfRooms, maxSize, minSize);
        spawnPlayer();
        render();

}
