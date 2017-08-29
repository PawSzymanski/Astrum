#include "game_over_system.h"
#include "ResourceManager.h"


game_over_system::game_over_system() :doEnd(false), licznik(0)
{
	
}

void game_over_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	CargoSpace::Handle cargoSpaceH;
	if(ResourcesManager::getInstanceRef().isGameOver ||
		(ResourcesManager::getInstanceRef().mainEvent->type == sf::Event::KeyPressed && ResourcesManager::getInstanceRef().mainEvent->key.code == sf::Keyboard::Escape))
	{
		
	}
	else
	for (auto en1 : en.entities_with_components(cargoSpaceH))
	{
		if (!cargoSpaceH->checked)
			return;
	}
	if (ResourcesManager::getInstanceRef().areAllPlatfIncluded == true || ResourcesManager::getInstanceRef().isGameOver == true)
	{
		if (!newEntity1.valid())
		{
			newEntity1 = en.create();

			newEntity1.assign<VertexArray>(ResourcesManager::getInstanceRef().vertCont.getPoly("faded_screen"),
				ResourcesManager::getInstanceRef().vertCont.getNormals("faded_screen"));
			newEntity1.assign<PolyName>("faded_screen3"); // just for render to let know what texture 
			newEntity1.assign<Transform>(sf::Vector2f(0, 0), 0);
			VertexArray::Handle txtToRender = newEntity1.component<VertexArray>();
		}

		for (auto &button : ResourcesManager::getInstanceRef().GOButton)
		{
			button.rect.corner_radius = 0.2;
			button.rect.size = sf::Vector2f(1.5, 0.3);
			button.rect.setOrigin(0.65, 0.05);
			button.rect.setFillColor(sf::Color(0, 0, 0, 0));
			button.rect.setOutlineColor(sf::Color::White);
			button.rect.setOutlineThickness(0.1);

			if (ResourcesManager::getInstanceRef().mainEvent && 
				ResourcesManager::getInstanceRef().mainEvent->type == sf::Event::MouseMoved &&
				ResourcesManager::getInstanceRef().mainEvent->mouseMove.x  > button.rect.getPosition().x * 78 -80 &&
				button.rect.getPosition().x * 78 + 80 > ResourcesManager::getInstanceRef().mainEvent->mouseMove.x &&
				ResourcesManager::getInstanceRef().mainEvent->mouseMove.y  > button.rect.getPosition().y * 76 -20 &&
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
						ResourcesManager::getInstanceRef().areAllPlatfIncluded = false;
						ResourcesManager::getInstanceRef().isGameOver = false;
						
						newEntity1.destroy();
					}
					else if (button.text.getString() == "Exit")
					{
						ResourcesManager::getInstanceRef().menu_stage.set();
						ResourcesManager::getInstanceRef().isGameOver = false;
						ResourcesManager::getInstanceRef().areAllPlatfIncluded = false;

						newEntity1.destroy();
					}
					else if (button.text.getString() == "Next")
					{
						ResourcesManager::getInstanceRef().lvl_set_stage.set();
						ResourcesManager::getInstanceRef().isGameOver = false;
						ResourcesManager::getInstanceRef().areAllPlatfIncluded = false;
				
						newEntity1.destroy();
					}
				}
			}	
		}
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
