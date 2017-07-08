#include "player_input_system.h"
#include "ResourceManager.h"


player_input_system::player_input_system() 
{
}

void player_input_system::init()
{

}


void player_input_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{

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
	auto &ex = ResourcesManager::getInstanceRef().ex;
	auto &phisics = ResourcesManager::getInstanceRef().phisics;

    vertCont.addPoly(potato, 6, "potato");


	auto poly1 = ex.entities.create();
	auto poly2 = ex.entities.create();
	auto poly3 = ex.entities.create();

	std::cout << "SSSSSSSSSSSSSSIZE :" << ex.entities.size() << std::endl;

    phisics.createPolygon(poly1, sf::Vector2f(8.75, 10.15), sf::Vector2f(0, 0), 0, 0, "wall");
    phisics.createPolygon(poly2, sf::Vector2f(0.5, 4.5), sf::Vector2f(0, 0), 90, 0, "wall");
    phisics.createPolygon(poly3, sf::Vector2f(17, 4.5), sf::Vector2f(0, 0), 90, 0,  "wall");

	auto player1 = ex.entities.create();
    phisics.createPolygon(player1, sf::Vector2f(1.5, 9), sf::Vector2f(0, 0), 0, 1, "TRIANGLE_BODY");


	auto engine1 = ex.entities.create();

	engine1.assign<Position>(sf::Vector2f(0, 0));
	engine1.assign<ForcePoint>(sf::Vector2f(0, 0), sf::Vector2f(0, -0.2));
    engine1.assign<KeyAssigned>(sf::Keyboard::X);
	engine1.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);

	auto engine2 = ex.entities.create();
	engine2.assign<Position>(sf::Vector2f(0, 0));
	engine2.assign<ForcePoint>(sf::Vector2f(0.5, 0), sf::Vector2f(0, -0.2));
    engine2.assign<KeyAssigned>(sf::Keyboard::Z);
	engine2.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);

	auto engine3 = ex.entities.create();
	engine3.assign<Position>(sf::Vector2f(0, 0));
	engine3.assign<ForcePoint>(sf::Vector2f(-0.5, 0), sf::Vector2f(0, -0.2));
    engine3.assign<KeyAssigned>(sf::Keyboard::C);
	engine3.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);
}

player_input_system::~player_input_system()
{
}
