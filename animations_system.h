#pragma once
#include "LibsAndDeclarations.h"


class animations_system : public entityx::System<animations_system>
{
public:
	animations_system();

	void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);

	~animations_system();
};

