#include <iostream>
#include "tinyxml2.h"
#include "include.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <math.h>

using namespace std;
using namespace tinyxml2;

DungeonControler::DungeonControler() : level(1)
{
}

void DungeonControler::readEntityXml(string xmlName)
{
	xmlName = "xml/"+xmlName;
	const char* xmlFileName = xmlName.c_str();
	cout << "Converted string file to " << xmlFileName << endl;
      // Opens the xml file
      XMLDocument doc;
      doc.LoadFile(xmlFileName);

      XMLElement* parent = doc.FirstChildElement("Entity");
      
      //Loads entity content
	// Icon element
	XMLElement* iconElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Icon");
        const char* icon = iconElement->GetText();

      // Name element
      XMLElement* nameElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Name");
        const char* name = nameElement->GetText();

      // Description element
        XMLElement* discriptionElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Description");
        const char* description = discriptionElement->GetText();

      // Health element
        XMLElement* healthElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Health");
        const char* health = healthElement->GetText();

	// Strength element
        XMLElement* strengthElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Strength");
        const char* strength = strengthElement->GetText();

	// Defense element
        XMLElement* defenseElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Defense");
        const char* defense = defenseElement->GetText();

	// Range element
        XMLElement* rangeElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Range");
        const char* range = rangeElement->GetText();

	// Intelligence element
        XMLElement* intelligenceElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Intelligence");
        const char* intelligence = intelligenceElement->GetText();

	string Icon = icon; // Converts the char to a string

	// Creates an entity object within a vector
	entitys.push_back(Entity(Icon, name, description, atoi(health), atoi(strength), atoi(defense), atoi(range), atoi(intelligence)));
}

void DungeonControler::loadContent()
{
	//Makes an array of the xml files
	system("cd xml/ && rm listOfEntitys.txt && ls *entity.xml >> listOfEntitys.txt"); // Removes previous listOfFiles.txt
	ifstream xmlEntitys;
	xmlEntitys.open("xml/listOfEntitys.txt");

	vector<string> xmlEntitysRead(1);
	string currentLine;

	while(getline(xmlEntitys, currentLine))
	{
		xmlEntitysRead.push_back(currentLine);
	}

	cout << "Read files!  There are " << xmlEntitysRead.size() << " .xml files" << endl;

	// Sends list of entity file names to readEntityXml()
	for(int i = 1; i < xmlEntitysRead.size(); i ++)
	{
		cout << "Reading " << xmlEntitysRead[i] << endl;
		readEntityXml(xmlEntitysRead[i]);
	}
}

void DungeonControler::printLoadedXml()
{
	cout << "----------------------------------" << endl;
	for(int id = 0; id < entitys.size(); id++)
	{
		cout << "ENTITY " << id << endl;
		cout << "Icon:" << entitys[id].icon << endl;
		cout << "Name:" << entitys[id].name << endl;
		cout << "Description:" << entitys[id].description << endl;
		cout << "Health:" << entitys[id].health << endl;
		cout << "Strength:" << entitys[id].strength << endl;
		cout << "Defense:" << entitys[id].defense << endl;
		cout << "Range:" << entitys[id].range << endl;
		cout << "Intelligence:" << entitys[id].intelligence << endl;
		cout << "Challenge Rating:" << entitys[id].CR() << endl;
		cout << "------------------------------------" << endl << endl;
	}
}

void DungeonControler::calculateDifficulty()
{
	double magnitude = 10 * log10( ( (double)level ) + 1); // This is a dificulty curve, the entitys level become
	cout << magnitude << endl;

	// Solving the x intercepts for the quadratic formula used to find the range
	// Setting tmp values so solving for the x's is easier to follow
	double A = -1;
	double B = -2 * (double)level;
	double C = -( pow( (double)level, 2) - magnitude );


	// Calculates a range for CR
	minLevel = - (-B - sqrt( pow(B, 2) - 4 * A * C ) ) / ( 2 * A );
	maxLevel = - (-B + sqrt( pow(B, 2) - 4 * A * C ) ) / ( 2 * A );

	cout << minLevel << " " << maxLevel << endl;

	if(minLevel <= 0) minLevel = 0;
}

void DungeonControler::sortEntitys()
{
	Entity tmp; // stores a temperary entity so that they can be swapped
	for(int j = 0; j < entitys.size(); j ++)
	{
		for(int i = 0; i < entitys.size(); i ++)
		{
			if(entitys[i].CR() > entitys[j].CR())
			{
				tmp = entitys[j];
				entitys[j] = entitys[i];
				entitys[i] = tmp;
			}
		}
	}
}

void DungeonControler::generateEntitys()
{
	// Calculates how many entitys/what entitys should be spawned depending on the map level/players level(?)
	calculateDifficulty();
	cout << "Generating an array of entitys that's CR ratings are between " << (int)minLevel << " - " << (int)maxLevel << endl;
	int rangeMedian = ((int)minLevel + (int)maxLevel) / 2;

	amountOfEntitys = 3+rand() % rangeMedian;
	cout << amountOfEntitys << endl;

	for(int id = 0; id < amountOfEntitys; id ++)
	{
		int selectedEntity = rand() % entitys.size();
		generatedEntityList[id] = entitys[selectedEntity];
		cout << "Adding " << generatedEntityList[id].name << " with CR of " << generatedEntityList[id].CR() << " to the entity list" << endl;
	}
}

void DungeonControler::createMap()
{
	cout << amountOfEntitys << endl;
	Map m(amountOfEntitys, generatedEntityList);
	m.init("Caves");
}

void DungeonControler::init()
{
	// Loads content
	loadContent();
	sortEntitys();
	printLoadedXml();
	
	generateEntitys();

	createMap();
}
