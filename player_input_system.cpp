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
	std::string typeOfElement;
	float xPos, yPos, xVel, yVel, rot, mass;

	parser.setSection("world");
	while (!parser.EndOfSection())
	{
		std::cout << "XXXXXXXXXXXXXXXXXXxx" << std::endl;
		typeOfElement = parser.getString();
		xPos = parser.getFloat();
		std::cout << "X: " << xPos << std::endl;
		yPos = parser.getFloat();
		std::cout << "Y: " << yPos << std::endl;
		xVel = parser.getFloat();
		yVel = parser.getFloat();
		rot = parser.getFloat();
		mass = parser.getFloat();
		auto poly = en.create();
		phisics.createPolygon(poly, sf::Vector2f(xPos, yPos), 
			sf::Vector2f(xVel, yVel), rot, mass, typeOfElement);
	
	}
	sf::VertexArray potato(sf::TriangleFan, 6);

	potato[0].position = sf::Vector2f(-0.4, -0.5);
	potato[0].color = sf::Color::Yellow;
	potato[1].position = sf::Vector2f(0.6, -0.5);
	potato[1].color = sf::Color::Yellow;
	potato[2].position = sf::Vector2f(0.8, -0.2);
	potato[2].color = sf::Color::Yellow;
	potato[3].position = sf::Vector2f(0.3, 0.4);
	potato[3].color = sf::Color::Yellow;
	potato[4].position = sf::Vector2f(-0.7, 0.9);
	potato[4].color = sf::Color::Yellow;
	potato[5].position = sf::Vector2f(-0.8, -0.0);
	potato[5].color = sf::Color::Yellow;

	auto &vertCont = ResourcesManager::getInstanceRef().vertCont;

    vertCont.addPoly(potato, 6, "potato");

	auto player1 = en.create();
    phisics.createPolygon(player1, sf::Vector2f(1.5, 9), sf::Vector2f(0, 0), 0, 1, "TRIANGLE_BODY");


	auto engine1 = en.create();

	engine1.assign<Position>(sf::Vector2f(0, 0));
	engine1.assign<ForcePoint>(sf::Vector2f(0, 0), sf::Vector2f(0, -0.2));
    engine1.assign<KeyAssigned>(sf::Keyboard::X);
	engine1.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);

	auto engine2 = en.create();
	engine2.assign<Position>(sf::Vector2f(0, 0));
	engine2.assign<ForcePoint>(sf::Vector2f(0.5, 0), sf::Vector2f(0, -0.2));
    engine2.assign<KeyAssigned>(sf::Keyboard::Z);
	engine2.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);

	auto engine3 = en.create();
	engine3.assign<Position>(sf::Vector2f(0, 0));
	engine3.assign<ForcePoint>(sf::Vector2f(-0.5, 0), sf::Vector2f(0, -0.2));
    engine3.assign<KeyAssigned>(sf::Keyboard::C);
	engine3.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);
}

player_input_system::~player_input_system()
{
}
