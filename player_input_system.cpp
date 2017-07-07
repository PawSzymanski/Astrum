#include "player_input_system.h"
#include "ResourceManager.h"


player_input_system::player_input_system() 
{
}

void player_input_system::init()
{
	sf::VertexArray triangle(sf::TriangleFan, 3);

	triangle[0].position = sf::Vector2f(-0.5, -0.5);
	triangle[0].color = sf::Color::Red;
	triangle[1].position = sf::Vector2f(0.5, -0.5);
	triangle[1].color = sf::Color::Yellow;
	triangle[2].position = sf::Vector2f(0, 1);
	triangle[2].color = sf::Color::White;

	sf::VertexArray long_rect(sf::TriangleFan, 4);

	long_rect[0].position = sf::Vector2f(-9.5, -0.2);
	long_rect[0].color = sf::Color::Black;
	long_rect[1].position = sf::Vector2f(9.5, -0.2);
	long_rect[1].color = sf::Color::Black;
	long_rect[2].position = sf::Vector2f(9.5, 0.2);
	long_rect[2].color = sf::Color::Black;
	long_rect[3].position = sf::Vector2f(-9.5, 0.2);
	long_rect[3].color = sf::Color::Black;

	auto &vertCont = ResourcesManager::getInstanceRef().vertCont;
	auto &ex = ResourcesManager::getInstanceRef().ex;
	auto &phisics = ResourcesManager::getInstanceRef().phisics;


	vertCont.addPoly(triangle, 3);
	vertCont.addPoly(long_rect, 4);


	auto poly1 = ex.entities.create();
	//phisics.createPolygon(poly1, sf::Vector2f(8.75, 10.15), sf::Vector2f(0, 0), 0, 0, 1);
}


void player_input_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	auto &ex = ResourcesManager::getInstanceRef().ex;
	
	ex.systems.update<engine_system>(dt);
}

player_input_system::~player_input_system()
{
}
