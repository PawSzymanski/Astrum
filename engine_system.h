#pragma once
#include "LibsAndDeclarations.h"

class engine_system : public entityx::System<engine_system>, public entityx::Receiver<engine_system>
{
	bool boolHelp;
	sf::Transform matrix;

	void enginePart(entityx::Entity enPlayer, entityx::Entity enPart, entityx::EventManager & ev, AttachToPlayerPoint::Handle attachPointH, sf::Transform rotMatrix);
public:
	engine_system(entityx::EventManager &ev);

	void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);

	void receive(const ApplyForceEvent & ev);

	~engine_system();
};

