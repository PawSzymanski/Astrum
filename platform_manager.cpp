#include "platform_manager.h"



platform_manager::platform_manager(entityx::EventManager &ev) : isPlatColliding(false)
{
	ev.subscribe<CollisionEvent>(*this);
}


platform_manager::~platform_manager()
{
}

void platform_manager::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	if (isPlatColliding) 
	{
		if (clock.getElapsedTime().asMilliseconds() < 50)
		{
			time += clock.getElapsedTime();
			std::cout << clock.getElapsedTime().asMilliseconds() << "    " << time.asMilliseconds() << std::endl;

			if (time.asSeconds() > 3)
			{
				std::cout << "here i am" << std::endl;

				system("pause");
			}
		}
		else
		{
			time = sf::Time::Zero;
		}
		isPlatColliding = false;
		clock.restart();
	}
	else 
	{
	}
}

void platform_manager::receive(const CollisionEvent & ev)
{
	//LinearVelocity::Handle velH;

	entityx::Entity en = ev.en1;
	
	if (ev.en1.has_component<isPlatform>() && ev.en2.has_component<isPlayer>()
		|| ev.en1.has_component<isPlayer>() && ev.en2.has_component<isPlatform>())
	{
		isPlatColliding = true;
	}

}