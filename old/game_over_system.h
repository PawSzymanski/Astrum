#pragma once
#include "LibsAndDeclarations.h"

class game_over_system : public entityx::System<game_over_system>
{
	bool doEnd;
	int licznik;
	entityx::Entity newEntity1;
	entityx::Entity newEntity2;
	ButtonMenu buttonn[3];
public:
	game_over_system();

	void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);

	~game_over_system();
};
