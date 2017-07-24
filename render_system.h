#pragma once
#include "LibsAndDeclarations.h"

class render_system : public entityx::System<render_system>
{
	sf::RenderWindow &win;
	sf::Texture engineTexture;
	
public:
	render_system(sf::RenderWindow &window);

	void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);
	~render_system();
};

