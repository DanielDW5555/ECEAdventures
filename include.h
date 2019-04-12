#include <vector>

enum classType
{
	humanoid,  // Human like entitys (ex: Humans)
	construct, // Magical or Eletric powered entitys (ex: Mechanical Spider)
	elemental, // Magic infused or arcana based entitys (ex: Rock Golum, Mage)
};

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
	int defense;
	int range = 1;
	int exp = 0;
	int expToNextLevel();
	int checkExp(); // Checks to see if the player will level up
	int CR();		// Challenge rating calculation

	classType type = classType::humanoid;

	std::string name;
	std::string description;

	//Render/display settings
	std::string getIcon();
	std::string icon;

	// Constructors
	// Player(int level, int health, int maxHealth, int strength, int defense, int range, int exp);
};

class Entity
{
  public:
	int damage(); // Damage stats of an entity
	void checkDeath();
	int CR(); // Challenge rating calculation

	// Moement misc.
	int x;
	int y;

	// Entity stats
	int health;
	int strength;
	int defense;
	int range;
	int intelligence;
	bool isDead;

	classType type;

	std::string name;
	std::string description;

	char relation = 'e'; // 'e' for enemy, 'f' for friendly

	// Render/display settings
	std::string icon = "?";

	// Constructors
	Entity(std::string icon, std::string name, std::string description, int health, int strength, int defence, int range, int intellegence, classType type);
	Entity();
};

class Tile
{
  public:
	void setTile(std::string x);	 // Discribes the tile's structure (room tile, wall tile, ext)
	void setState(char wantedState); // Discribes the tiles current state such as storing the player, entities, items, ext
	std::string getTile();

	char state = ' ';

	bool isCenterTile = false; // Creates lines to connect other 'center tiles'
  private:
	std::string tile = " ";
};

class Map
{
  private:
	const int width = 70;
	const int height = 35;
	int numberOfRooms;
	int numberOfEntitys = 1;
	int wormX = 1;
	int wormY = 1;

  public:
	// Map Updates
	void init(std::string typeOfDungeon);
	void update();		 // The overall game loop
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
	void printEntityStats();

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
	void moveIntelligence0(int entityId);
	void moveIntelligence1(int entityId);
	bool moveRequest(int x, int y, char direction);

	// Misc functions
	double isEffective(classType attackingType, classType defendingType);

	// Objects/Constructors
	Map(int numberOfEntitys, Entity e[30]);
	Player p;
	Tile t[70][35];
	Entity e[30];
};

class DungeonControler
{
  public:
	int level; // Current floor of the dungeon
	int amountOfEntitys;
	double minLevel;
	double maxLevel;

	void createMap();
	void generateEntitys();
	void sortEntitys();
	void calculateDifficulty();

	// Initalise content
	void init();
	void readEntityXml(std::string xmlFileName);
	void loadContent();

	// Debug functions
	void printLoadedXml();

	int numberOfEntitys;
	std::string floorType;
	std::vector<Entity> entitys;

	Entity generatedEntityList[30];
	DungeonControler();
};
