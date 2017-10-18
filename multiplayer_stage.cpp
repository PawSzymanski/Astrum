#include "multiplayer_stage.h"
#include "ResourceManager.h"


multiplayer_stage::multiplayer_stage()
{
}

bool multiplayer_stage::init()
{
	return true;
}

void multiplayer_stage::input(sf::Event & event)
{
	auto & resource = ResourcesManager::getInstanceRef();
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			ResourcesManager::getInstanceRef().login_stage.set();
		}
	}
}

bool multiplayer_stage::update(float dt)
{
	
	return true;
}

void multiplayer_stage::render(sf::RenderWindow & window)
{
}

void multiplayer_stage::release()
{
}


multiplayer_stage::~multiplayer_stage()
{
}
