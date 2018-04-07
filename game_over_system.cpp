#include "game_over_system.h"
#include "ResourceManager.h"

game_over_system::game_over_system() :doEnd(false), licznik(0)
{
	clock.restart();
	

	auto &resource = ResourcesManager::getInstanceRef();
	resource.winText.setScale(0.01,0.01);
	resource.winText.setCharacterSize(60);
	resource.winText.setFont(resource.font);
	resource.winText.setOrigin(330,0);
	resource.winText.setPosition(resource.camera.getCenter().x, resource.camera.getCenter().y / 3);
	resource.winText.setString("Congratulations you did it \n Your life is different now!");

}

void game_over_system::release()
{
	ResourcesManager::getInstanceRef().areAllPlatfIncluded = false;
	ResourcesManager::getInstanceRef().areAllCargoSpaceIncluded = false;
	ResourcesManager::getInstanceRef().isGameOver = false;

	for (auto &button : ResourcesManager::getInstanceRef().GOButton)
	{
		button.lock = false;
	}
	ResourcesManager::getInstanceRef().isPauseTime = false;

	newEntity1.destroy();
}


void game_over_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	auto &resource = ResourcesManager::getInstanceRef();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		resource.isPauseTime = true;
	}
	//std::cout << resource.areAllPlatfIncluded << resource.areAllCargoSpaceIncluded << std::endl;

	if ( ( resource.areAllPlatfIncluded == true && 
		   resource.areAllCargoSpaceIncluded == true ) ||
		   resource.isGameOver == true ||	
		   resource.isPauseTime == true)
	{
		if (resource.areAllPlatfIncluded == true &&
			resource.areAllCargoSpaceIncluded == true)
		{
			resource.GOButton[0].lock = true;
		}
		else if(!resource.isPauseTime)
		{
			resource.GOButton[0].lock = true;
		}
		resource.isGameOver = true;


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
		int buttPos = -1;
		//game over MENU case
		for (auto &button : ResourcesManager::getInstanceRef().GOButton)
		{
			//std::cout << "BUTTON DRAW" << std::endl;
			
			button.rect.corner_radius = 0.2;
			button.rect.size = sf::Vector2f(1.5, 0.3);
			button.rect.setOrigin(0.65, 0.05);
			button.rect.setFillColor(sf::Color(0, 0, 0, 0));
			button.rect.setOutlineColor(sf::Color::White);
			button.rect.setOutlineThickness(0.1);
			button.rect.setPosition(sf::Vector2f(resource.camera.getCenter().x, resource.camera.getCenter().y + buttPos));
			button.text.setPosition(sf::Vector2f(resource.camera.getCenter().x, resource.camera.getCenter().y + buttPos));
			++buttPos;
			//	
			if (button.lock)
			{
				button.rect.setFillColor(sf::Color(200,200,200,255));
				continue;
			}

			//std::cout << " xy: " << (button.rect.getPosition().x) << std::endl;

			if (ResourcesManager::getInstanceRef().mainEvent &&
				ResourcesManager::getInstanceRef().mainEvent->type == sf::Event::MouseMoved &&
				ResourcesManager::getInstanceRef().mainEvent->mouseMove.x > (button.positionOnScreen.x) * 78 - 80 &&
				(button.positionOnScreen.x) * 78 + 80 > ResourcesManager::getInstanceRef().mainEvent->mouseMove.x &&
				ResourcesManager::getInstanceRef().mainEvent->mouseMove.y > button.positionOnScreen.y * 76 - 20 &&
				button.positionOnScreen.y * 76 + 40 > ResourcesManager::getInstanceRef().mainEvent->mouseMove.y)
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
					else if (button.text.getString() == "Again")
					{
						ResourcesManager::getInstanceRef().gameplay_stage.set();
						release();
					}
				}
			}
		}
	}
	else
	{ }
	
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
