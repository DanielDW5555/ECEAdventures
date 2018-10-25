
/*
 * TODO
 * - Create an 'entity' class that spawns other creatures on the map that can move and interact with the player
 * - Create a log system that logs actions done by player or enemies
 * - Create a user input system that can take more than player movement (options such as move, attack, help, ext)
 * - Create another layer of logic for the tile class so that more data about the tile can be stored (such as if there is an entity on the tile, item on tile, ext)
 * - Create an tile where if the player walks on it the game ends
 *
 *   BUGS
 *   - When the player spawns it sometimes causes an infinite loop
 */
class Player
{
        public:
		int damageStats();

		// Movement misc.
		int x = 0;
		int y = 0;
		
		// Player stats
		int level = 1;
		int health = 5;
		int maxHealth = 5;
		int strength = 2;
		int defence;
		int range = 1;
		int exp = 0;
		int expToNextLevel = 2;

		//Render/display settings
		std::string getIcon();
		std::string icon;
};

class Entity
{
	public:
		int damageStats();  // Damage stats of an entity
		void checkDeath();

		// Moement misc.
		int x;
		int y;

		// Entity stats
		int health;
		int strength;
		int defence;
		int range;
		int intelegence;
		bool isDead;

		char relation = 'e'; // 'e' for enemy, 'f' for friendly

		// Render/display settings
		char icon = 'm';
};

class Tile
{
	public:
		void setTile(std::string x);  // Discribes the tile's structure (room tile, wall tile, ext)
		void setState(char wantedState);  // Discribes the tiles current state such as storing the player, entities, items, ext
		std::string getTile();

		char state = ' ';

		bool isCenterTile = false;  // Creates lines to connect other 'center tiles'
	private:
		std::string tile = " ";
};

class Map
{
	private:
		const int width = 40;
		const int height = 20;
		int numberOfRooms;
		int numberOfEntitys = 10;
		int wormX = 1;
		int wormY = 1;
	public:
		// Map Updates
		void init(std::string typeOfDungeon);
		void update(); // The overall game loop
		void updateStates(); // Updates the states of each tile
		void createMap(int numberOfRooms, int roomWidth, int roomHeight);

		// Spawning functions
		void spawnPlayer();
		void spawnEntity(int numberOfEntitys);
		void entityInit(int numberOfEntitys, std::string dungeonType); // Configures the entity based on the map type and player level
		
		// Render functions
		void render();
		void debugRender(); // Renders the image to show more information about each tile
		void printPlayerStats();

		// Save/Load txt files functions
		void saveLog(std::string textToSave);
		void loadLog(int numberOfLogs); // Prints the newest logs in cout
		
		// Move related functions
		void playerTurn();
		void movePlayer(char direction);
		void playerAttack(char direction);
		void entityTurn();
		char entityAttackCheck(int id);
		void entityAttack(int id, char direction);
		void moveEntity(int id);
		bool moveRequest(int x, int y, char direction);

		// Objects
		Map();
		Player p;
		Tile t[40][20];
		Entity e[];
};

class DungeonControler
{
	public:
		void createMap();

		// Initalise content
		void loadContent();
		
		int numberOfEntitys;
		std::string floorType;

};
