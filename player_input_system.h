#pragma once
#include "LibsAndDeclarations.h"
#include "engine_system.h"

class player_input_system : public entityx::System<player_input_system> 
{
	Phisics_2D &phisics;


public:

	player_input_system(Phisics_2D &);
	
	void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);
	
	void init();

	~player_input_system();

};

