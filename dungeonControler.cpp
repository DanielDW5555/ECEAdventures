#include <iostream>
#include "tinyxml2.h"
#include "include.h"
using namespace std;
using namespace tinyxml2;

void DungeonControler::loadContent()
{
	// Opens the xml file
	XMLDocument doc;
	doc.LoadFile("xml.xml");

	XMLElement* parent = doc.FirstChildElement("Entity");
	
	//Loads entity content
	// Name element
	XMLElement* nameElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Name");
        const char* name = nameElement->GetText();
        printf( "Name: %s\n", name );

	// Description element
        XMLElement* discriptionElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Description");
        const char* description = discriptionElement->GetText();
        printf( "Description: %s\n", description );

	// Health element
        XMLElement* healthElement = doc.FirstChildElement("Entity")->FirstChildElement("Mandatory")->FirstChildElement("Health");
        const char* health = healthElement->GetText();
        cout << "Health: " << health << endl;

	for (const XMLElement* child = parent->FirstChildElement(); child!=0; child=child->NextSiblingElement())
	{
		child->FirstChildElement("Mandatory")->FirstChildElement("Name");
		const char* name2 = nameElement->GetText();
        	printf( "Name: %s\n", name2 );
	}
}

void DungeonControler::createMap()
{
	Map m;
	m.init("Caves");
}
