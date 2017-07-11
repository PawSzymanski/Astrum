#pragma once
#include "LibsAndDeclarations.h"

class engine_system : public entityx::System<engine_system>, public entityx::Receiver<engine_system>
{
public:
	engine_system(entityx::EventManager &ev);

	void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);

	void receive(const ApplyForceEvent & ev);

	~engine_system();
};

