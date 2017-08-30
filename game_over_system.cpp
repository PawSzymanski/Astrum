#include "game_over_system.h"
#include "ResourceManager.h"

game_over_system::game_over_system() :doEnd(false), licznik(0)
{
	clock.restart();
}

void game_over_system::release()
{
	ResourcesManager::getInstanceRef().areAllPlatfIncluded = false;
	ResourcesManager::getInstanceRef().areAllCargoSpaceIncluded = false;
	ResourcesManager::getInstanceRef().isGameOver = false;

	newEntity1.destroy();
}

void game_over_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	auto &resource = ResourcesManager::getInstanceRef();

	if (time.asSeconds() > 1 && (ResourcesManager::getInstanceRef().isGameOver == true &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
	{
		std::cout << "BUTTON OUT" << std::endl;
		release();
		time = sf::Time::Zero;
	}

	if (( resource.areAllPlatfIncluded == true &&
		ResourcesManager::getInstanceRef().areAllCargoSpaceIncluded == true) ||
		resource.isGameOver == true )
	{
		std::cout << "BUTTON IN" << std::endl;
		ResourcesManager::getInstanceRef().isGameOver = true;
		if (!newEntity1.valid())
		{
			clock.restart();
			newEntity1 = en.create();

			newEntity1.assign<VertexArray>(ResourcesManager::getInstanceRef().vertCont.getPoly("faded_screen"),
			ResourcesManager::getInstanceRef().vertCont.getNormals("faded_screen"));
			newEntity1.assign<PolyName>("faded_screen3"); // just for render to let know what texture 
			newEntity1.assign<Transform>(sf::Vector2f(0, 0), 0);
			VertexArray::Handle txtToRender = newEntity1.component<VertexArray>();
		}
		time += clock.restart();
		for (auto &button : ResourcesManager::getInstanceRef().GOButton)
		{
			std::cout << "BUTTON DRAW" << std::endl;

			button.rect.corner_radius = 0.2;
			button.rect.size = sf::Vector2f(1.5, 0.3);
			button.rect.setOrigin(0.65, 0.05);
			button.rect.setFillColor(sf::Color(0, 0, 0, 0));
			button.rect.setOutlineColor(sf::Color::White);
			button.rect.setOutlineThickness(0.1);

			if (ResourcesManager::getInstanceRef().mainEvent &&
				ResourcesManager::getInstanceRef().mainEvent->type == sf::Event::MouseMoved &&
				ResourcesManager::getInstanceRef().mainEvent->mouseMove.x > button.rect.getPosition().x * 78 - 80 &&
				button.rect.getPosition().x * 78 + 80 > ResourcesManager::getInstanceRef().mainEvent->mouseMove.x &&
				ResourcesManager::getInstanceRef().mainEvent->mouseMove.y > button.rect.getPosition().y * 76 - 20 &&
				button.rect.getPosition().y * 76 + 40 > ResourcesManager::getInstanceRef().mainEvent->mouseMove.y)
			{
				button.has_mouse = true;
			}
			else if (ResourcesManager::getInstanceRef().mainEvent->type == sf::Event::MouseMoved)
			{
				button.has_mouse = false;
			}
			if (button.has_mouse == true)
			{
				button.rect.setOutlineThickness(0.15);

				if (ResourcesManager::getInstanceRef().isMouseButtonReleased)
				{
					if (button.text.getString() == "Back")
					{
						release();
					}
					else if (button.text.getString() == "Exit")
					{
						ResourcesManager::getInstanceRef().menu_stage.set();
						release();
					}
					else if (button.text.getString() == "Next")
					{
						ResourcesManager::getInstanceRef().lvl_set_stage.set();
						release();
					}
				}
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		resource.isGameOver = true;
	}
	
	AdditionalAnim::Handle additH;
	for (auto e : en.entities_with_components(additH))
	{
		additH = e.component<AdditionalAnim>();
		if (additH->wholeTime.asSeconds() > 4 && additH->nameOfAnim == "explosion")
		{
			e.remove<AdditionalAnim>();
		}
	}
}


game_over_system::~game_over_system()
{
}
