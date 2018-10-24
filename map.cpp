#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

		// Sets the center tile in the box as a 'center tile' and places the worm there
		t[(x+rWidth/2)][y+rHeight/2].isCenterTile = true;
		wormX = (x+rWidth/2);
		wormY = (y+rHeight/2);
                
                //Checks the room width and height to make sure its biger than minSize
                while(rWidth < minSize) rWidth = rand() % maxSize;
                while(rHeight < minSize) rHeight = rand() % maxSize;
                
                //Once rooms are propper size, check to see if the room fits on the map
                while( (x+rWidth) >= width-1) x = rand() % width-1;
                while( (y+rHeight) >= height-1) y = rand() % height-1;
                
                // Setting tiles to be the shapes of the rooms at random x and y locations
                for(int j = 0; j < height; j ++)
                {
                        for(int i = 0; i < width; i ++)
                        {
                                if(i >= x && i <= (x+rWidth) && j >= y && j <= (y+rHeight)) // If loop is at the correct cords to make a room, generate
				{
                                        t[i][j].setTile("r");
				}
                        }
                }

        }
	// Connects the tiles with the 'center tile' together
	for(int j = 0; j < height; j ++)
	{
		for(int i = 0; i < width; i ++)
		{
			if(t[i][j].isCenterTile == true)
			{
			// Created a worm to eat away the rooms?
				while(wormY != j or wormX != i)
				{
					int choice = rand() % 2;
					if(wormY > j && choice == 1)
					{
						wormY = wormY - 1;
						t[wormX][wormY].setTile("r");
					}
					else if(wormY < j && choice == 1)
					{
						wormY = wormY + 1;
						t[wormX][wormY].setTile("r");
					}
					else if(wormX > i && choice == 0)
					{
						wormX = wormX - 1;
						t[wormX][wormY].setTile("r");
					}
					else if(wormX < i && choice == 0)
					{
						wormX = wormX + 1;
						t[wormX][wormY].setTile("r");
					}
				}	
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
			else if(t[i][j].state == 'e')
			{
				for(int id = 0; id < numberOfEntitys+1; id ++)
				{
					if(e[id].x == i and e[id].y == j)
					{
						cout << e[id].icon;
					}
				}
			}
			else if(t[i][j].getTile() == "r") cout << "."; // Prints a room tile as an empty tile
                }
                cout << endl;
        }

	// Renders the players stats after the map has been rendered
	printPlayerStats();

	// Prints the newest logs
	loadLog(5);
}

// Formats the player stats so that it is rendered evenly depending on the width of the map
void Map::printPlayerStats()
{
	// Renders players icon
	cout << p.icon << ":" << endl;

	// Renders the player health
	string playerHealth = "HP:"+to_string(p.health)+" [";
	double healthBarWidth = width-playerHealth.size()-1;
	double healthPercent = (double)p.health/(double)p.maxHealth;
	double amountOfHpToRender = healthPercent*healthBarWidth;

	cout << playerHealth;
	for(int i = 0; i < width-playerHealth.size()-1; i ++)
	{
		if(i < amountOfHpToRender) cout << "▓";
		else cout << ' ';
	}
	cout <<  ']';
	cout << endl;

	string playerExp = "EXP:"+to_string(p.exp)+" [";
	double expBarWidth = width-playerExp.size()-1;
	double expPercent = (double)p.exp/(double)p.expToNextLevel;
	double amountOfExpToRender = expPercent*expBarWidth;

	cout << playerExp;
	for(int i = 0; i < width-playerExp.size(); i ++)
	{
		if(i < amountOfExpToRender) cout << "▒";
		else cout << ' ';
	}
	cout << ']';
	cout << endl;
}

void Map::saveLog(string text)
{
	ofstream saveText ("logs/logs.txt", std::ios_base::app);
	saveText << text+"\n";
	saveText.close();
}

void Map::loadLog(int numberOfLogs)
{
	// Gets number of logs in logs.txt
	ifstream loadText;
	loadText.open("logs/logs.txt");
	int numberOfLines = 0;
	string line = "";
	while(getline(loadText, line)) numberOfLines++;
	loadText.close();

	// Prints the newest logs
	loadText.open("logs/logs.txt");
	cout << "Log Journal:" << endl;
	int currentLine = 0;
	while(getline(loadText, line))
	{
		if(currentLine >= numberOfLines-numberOfLogs)
		{
			cout << line << endl;
		}
		currentLine ++;
	}
	loadText.close();
}

void Map::debugRender()
{
	cout << "DEBUG RENDER" << endl;
	for(int j = 0; j < height; j ++)
	{
		for(int i = 0; i < width; i ++)
		{
			cout << t[i][j].state;
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
}

void Map::spawnEntity(int numberOfEntitys)
{
	for(int id = 0; id < numberOfEntitys; id ++)
	{
		cout << "Spawning monster " << id << endl;
		int randX = rand() % width;
		int randY = rand() % height;
		while(t[randX][randY].getTile() != "r")
		{
			randX = rand() % width;
			randY = rand() % height;
			cout << "Attempting to spawn at: " << randX << " " << randY << endl;
		}
        	e[id].x = randX;
        	e[id].y = randY;

		// Sets random health based on the type/class of entity
		e[id].health = (rand() % 3)+1;
		e[id].range = 1;
		e[id].strength = 1;
		e[id].isDead = false;
		e[id].icon = 'm';
	}
	
}

void Map::entityInit(int numberOfEntitys, string dungeonType)
{
	for(int id = 0; id < numberOfEntitys; id++)
	{
		e[id].intelegence = 0;
	}
}

// This is called whenever an entity wants to move on the map
bool Map::moveRequest(int x, int y, char direction)
{
	if(direction == 'd' && t[x+1][y].getTile() == "r" && t[x+1][y].state != 'e' && t[x+1][y].state != 'p') return 1;
	else if(direction == 'a' && t[x-1][y].getTile() == "r" && t[x-1][y].state != 'e' && t[x-1][y].state != 'p') return 1;
	else if(direction == 'w' && t[x][y-1].getTile() == "r" && t[x][y-1].state != 'e' && t[x][y-1].state != 'p') return 1;
	else if(direction == 's' && t[x][y+1].getTile() == "r" && t[x][y+1].state != 'e' && t[x][y+1].state != 'p') return 1;
	else return 0;
}

void Map::movePlayer(char direction)
{
	if(direction == 'w') p.y--;
        else if(direction == 's') p.y++;
        else if(direction == 'a') p.x--;
        else if(direction == 'd') p.x++;
}

void Map::playerAttack(char direction)
{
	int playerDamage = p.damageStats();
	int entityId;
	for(int id = 0; id < numberOfEntitys; id++)
	{
		if(direction == 'i' and t[p.x][p.y-p.range].state == 'e')
		{
			cout << "Player is attacking the enemy to the up!" << endl;
				if(e[id].x == p.x and e[id].y == p.y-p.range)
				{
					e[id].health = e[id].health - playerDamage;
					string entityIcon = string(1, e[id].icon);
        				string playerDmg = to_string(playerDamage);
        				string logs = p.icon + ": delt " + playerDmg + " to " + entityIcon;
        				saveLog(logs);
				}
		}
		else if(direction == 'k' and t[p.x][p.y+p.range].state == 'e')
                {
			cout << "Player is attacking the enemy to the down!" << endl;
                                if(e[id].x == p.x and e[id].y == p.y+p.range)
				{
					e[id].health = e[id].health - playerDamage;
					string entityIcon = string(1, e[id].icon);
        				string playerDmg = to_string(playerDamage);
        				string logs = p.icon + ": delt " + playerDmg + " to " + entityIcon;
        				saveLog(logs);
				}
                }
		else if(direction == 'j' and t[p.x-p.range][p.y].state == 'e')
                {
			cout << "Player is attacking the enemy to the left!" << endl;
                                if(e[id].x == p.x-p.range and e[id].y == p.y)
				{
					e[id].health = e[id].health - playerDamage;
					string entityIcon = string(1, e[id].icon);
        				string playerDmg = to_string(playerDamage);
        				string logs = p.icon + ": delt " + playerDmg + " to " + entityIcon;
        				saveLog(logs);
				}
                }
		else if(direction == 'l' and t[p.x+p.range][p.y].state == 'e')
                {
			cout << "Player is attacking the enemy to the right!" << endl;
                                if(e[id].x == p.x+p.range and e[id].y == p.y)
				{
					e[id].health = e[id].health - playerDamage;
					string entityIcon = string(1, e[id].icon);
        				string playerDmg = to_string(playerDamage);
        				string logs = p.icon + ": delt " + playerDmg + " to " + entityIcon;
        				saveLog(logs);
				}
		}
	}
}

// Players actions that can be done per turn
void Map::playerTurn()
{
	bool hasMoved = false;
	while(hasMoved == false)
	{
		char turn;
        	cin >> turn;

		// Player movement
		if(turn == 'w' or turn == 'a' or turn == 's' or turn == 'd')
		{
        		if(moveRequest(p.x, p.y, turn))
        		{
                		movePlayer(turn);
				hasMoved = true;
        		}
        		else cout << "Somthing is in the way!" << endl;
		}

		// Player attack
		else if(turn == 'i' or turn == 'j' or turn == 'k' or turn =='l')
		{
			playerAttack(turn);
			hasMoved = true;
		}
	}
	updateStates();

}

// Moves entitys such as enemys or other movable objects depending on there intelegence
void Map::moveEntity(int id)
{
	// Stupid enemy movement
	if(e[id].intelegence == 0)
	{
        	bool hasMoved = false;
        	while(hasMoved == false)
        	{
        		int choice = rand() % 4;
                	switch(choice)
                	{
                	case 0:
                		if(moveRequest(e[id].x, e[id].y, 'w'))
                        	{
                        		e[id].y--;
                                	hasMoved = true;
				}
                        	break;
                	case 1:
                        	if(moveRequest(e[id].x, e[id].y, 's'))
                        	{
                                	e[id].y++;
                                	hasMoved = true;
                        	}
                        	break;
                	case 2:
                        	if(moveRequest(e[id].x, e[id].y, 'a'))
                        	{
                                	e[id].x--;
                        	break;
				}
                	case 3:
                        	if(moveRequest(e[id].x, e[id].y, 'd'))
                        	{
                                	e[id].x++;
                                	hasMoved = true;
                        	}
                        	break;
			}
                }
         }
}

void Map::entityAttack(int id, char direction)
{
	cout << "Player took " << e[id].damageStats();
	p.health = p.health - e[id].damageStats();
}

char Map::entityAttackCheck(int id)
{
	cout << "range" << e[id].range << endl;
	if(e[id].x == p.x and e[id].y-e[id].range == p.y)
        {
                return 'i';
        }
	if(e[id].x == p.x and e[id].y+e[id].range == p.y)
        {
                return 'k';
        }
	if(e[id].x-e[id].range == p.x and e[id].y == p.y)
        {
                return 'j';
        }
	if(e[id].x+e[id].range == p.x and e[id].y == p.y)
        {
                return 'l';
        }
	
	else return ' ';
}

void Map::entityTurn()
{
	// Cycles through each enemy, depending on their intelegence stat they will act diffrently
	for(int id = 0; id < numberOfEntitys; id ++)
        {
		e[id].checkDeath();
		if(e[id].isDead == false)
		{
			cout << "Attack check " << entityAttackCheck(id) << endl;
			if(entityAttackCheck(id) != ' ')
			{
				entityAttack(id, entityAttackCheck(id));
			}
			else
			{
				moveEntity(id);
			}
			updateStates();
		}

		cout << "Entity " << id << " health:" << e[id].health << endl;
	}
}

void Map::updateStates()
{
	// Resets the state 'board'
	for(int j = 0; j < height; j ++)
	{
		for(int i = 0; i < width; i ++)
		{
			t[i][j].state = ' ';
		}
	}
	// Updats the players states
	t[p.x][p.y].state = 'p';

	// Updates each entitys location / stat
	for(int z = 0; z < numberOfEntitys; z ++)
	{
		for(int j = 0; j < height; j ++)
		{
			for(int i = 0; i < width; i ++)
			{
				if(e[z].isDead == false) t[e[z].x][e[z].y].state = 'e';
				else t[e[z].x][e[z].y].state = '-';
			}
		}
	}
}

void Map::update()
{
	while(true)
	{
		srand(time(NULL));
		playerTurn();
		entityTurn();
		updateStates();
		render();
		// debugRender();
	}
}

// Creates a map
void Map::init(string dungeonType)
{
	// If a dungeon type is not specefied, it spawns a 'well rounded' dungeon
	int numberOfRooms = 5;
        int maxSize = 5;
        int minSize = 3;

	cout << dungeonType << endl;

	if(dungeonType == "Caves")
	{
		cout << "GENERATING CAVES" << endl;
		int numberOfRooms = 10;
        	int maxSize = 10;
        	int minSize = 4;
		createMap(numberOfRooms, maxSize, minSize);
		entityInit(numberOfEntitys, dungeonType);
        	spawnEntity(numberOfEntitys);

	}
	else
	{
		int numberOfRooms = 4;
		int maxSize = 10;
		int minSize = 2;
		createMap(numberOfRooms, maxSize, minSize);
        	spawnEntity(numberOfEntitys);
	}

	// Configures the player stats
	spawnPlayer();
	p.icon = "Ω"; 
	updateStates();
	render();
	update();

}

Map::Map() : numberOfEntitys(5)
{
}
