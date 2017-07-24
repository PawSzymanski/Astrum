#include "player_input_system.h"
#include "ResourceManager.h"


player_input_system::player_input_system(Phisics_2D &phs) : phisics(phs)
{
}

void player_input_system::init()
{

}

void player_input_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	ConfigParser parser;

	auto levelInfo = ResourcesManager::getInstanceRef().levelInfo;
	auto shipInfo = ResourcesManager::getInstanceRef().shipInfo;

	if (!parser.load(levelInfo))
	{
		assert(false);
	}
	std::string typeOfElement, pathToShip = "resources/parts/";
	float xPos, yPos, xVel, yVel, rot, mass;

	parser.setSection("world");
	while (!parser.EndOfSection())
	{
		typeOfElement = parser.getString();

		xPos = parser.getFloat();

		yPos = parser.getFloat();

		xVel = parser.getFloat();

		yVel = parser.getFloat();

		rot = parser.getFloat();

		mass = parser.getFloat();

		auto poly = en.create();
		
		phisics.createPolygon(poly, sf::Vector2f(xPos, yPos), 
			sf::Vector2f(xVel, yVel), rot, mass, typeOfElement);
	
	}

	//SHIP
	if (!parser.load(shipInfo))
	{
		assert(false);
	}
	std::cout << shipInfo << std::endl;
	parser.setSection("body_info");
	std::string typeOfShip, shipColor;
	
	while (!parser.EndOfSection())
	{
		typeOfShip = parser.getString();
	}
	
	if (typeOfShip.size() == 0)
	{
		auto &stage = ResourcesManager::getInstanceRef();
		std::cout << "WYBIERZ JAKIS STATEK" << std::endl;
		stage.creator_stage.set();	
	}
	parser.setSection("color");
	
	while (!parser.EndOfSection())
	{	
		shipColor = parser.getString();
	}
	
	
	auto playerEn = en.create();
	playerEn.assign<isPlayer>();
	phisics.createPolygon(playerEn, sf::Vector2f(2, 8),
		sf::Vector2f(0, 0), 0, 1, typeOfShip);
	

	
	//PARTS
	parser.setSection("parts_info");
	std::string partName, partKey, pathToPart, partColor, partVert;
	Conversion conversion;
	float partPosX, partPosY, partDegree;
	
	
	while (!parser.EndOfSection())
	{
		typeOfShip = parser.getString();
		partPosX = parser.getFloat();
		partPosY = parser.getFloat();
		partDegree = parser.getFloat();
		partKey = parser.getString();
		ConfigParser parser2;
	
		
		//PART INFO LOAD engine maybe legs or anything else
		pathToPart.clear();
		pathToPart.insert(pathToPart.size(), "resources/parts/");
		pathToPart.insert(pathToPart.size(), typeOfShip);
		pathToPart.insert(pathToPart.size(), ".cfg");
		if (!parser2.load(pathToPart))
		{
			assert(false);
		}
		while (!parser2.EndOfSection())
		{
			parser2.setSection("name");
			partVert = parser2.getString();	
		}

		auto &container = ResourcesManager::getInstanceRef().vertCont;

		auto partEn = en.create();
		
		sf::Vector2f engineForce = sf::Vector2f(0, -0.2);
		
		sf::Transform transForce;
		transForce.rotate(partDegree);
		engineForce = transForce * engineForce;
		
		partEn.assign<Rotation>(partDegree);
		partEn.assign<AttachToPlayerPoint>(sf::Vector2f(partPosX, partPosY));
		partEn.assign<VertexArray>(container.getPoly(partVert), container.getNormals(partVert));
		partEn.assign<Transform>(sf::Vector2f(0, 0), 0);
		partEn.assign<LinearVelocity>(sf::Vector2f(0, 0));

		std::cout<<std::endl;
		if (partVert.substr(0, 12) != "landing_legs")
		{
			std::cout << "engine loaded" << std::endl;
			partEn.assign<isEngine>();

			partEn.assign<ForcePoint>(engineForce);

			partEn.assign<KeyAssigned>(conversion.string_to_sf_key[partKey]);
		}
		else {
			std::cout << "legs loaded" << std::endl;

			partEn.assign<isLegs>();
		}
	}
}

player_input_system::~player_input_system()
{
}
