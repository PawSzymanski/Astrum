#pragma once
#include "LibsAndDeclarations.h"

class engine_system : public entityx::System<engine_system>
{
public:
	engine_system();

	void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);

	~engine_system();
};

