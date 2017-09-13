#pragma once
#include "LibsAndDeclarations.h"


class enemy_system : public entityx::System<enemy_system>
{
	bool dir;
	sf::Vector2f detectionSpace ;
	Phisics_2D & phisics;
	sf::Clock bulletClock;
	sf::Time bulletTime;
public:
	enemy_system(Phisics_2D &);
	void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);
	~enemy_system();
};


