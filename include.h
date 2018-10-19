
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
		int x = 0;
		int y = 0;
		std::string getIcon();
        private:
		std::string icon = "Ω";
};

class Tile
{
	public:
		void setTile(std::string x);
		std::string getTile();
	private:
		std::string tile = " ";
};

class Map
{
	private:
		const int width = 40;
		const int height = 20;
		int numberOfRooms;
	public:
		void init();
		void update();
		void spawnPlayer();
		void createMap(int numberOfRooms, int roomWidth, int roomHeight);
		void render();
		
		void movePlayer();
		bool moveRequest(int x, int y, char direction);
		Player p;
		Tile t[40][20];
};
