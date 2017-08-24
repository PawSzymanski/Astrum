#include "game_over_system.h"
#include "ResourceManager.h"


game_over_system::game_over_system() :doEnd(false), licznik(0)
{
//	buttonn[0].init(ResourcesManager::getInstanceRef().font, 1 , sf::Vector2f(8.75,4), sf::Color::White, "Ponów", sf::Vector2f(0.0,0.0));
//	buttonn[1].init(ResourcesManager::getInstanceRef().font, 1, sf::Vector2f(8.75, 5), sf::Color::White, "Next", sf::Vector2f(0.0, 0.0));
//	buttonn[2].init(ResourcesManager::getInstanceRef().font, 1, sf::Vector2f(8.75, 6), sf::Color::White, "Exit", sf::Vector2f(0.0, 0.0));
}

void game_over_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	CargoSpace::Handle cargoSpaceH;
	for (auto en1 : en.entities_with_components(cargoSpaceH))
	{
		if (!cargoSpaceH->checked)
			return;
	}
	if (ResourcesManager::getInstanceRef().areAllPlatfIncluded)
	{
	
			if (!newEntity1.valid())
				newEntity1 = en.create();
		//	if (!newEntity2.valid())
		//		newEntity2 = en.create();
		

		newEntity1.assign<VertexArray>(ResourcesManager::getInstanceRef().vertCont.getPoly("faded_screen"), 
		ResourcesManager::getInstanceRef().vertCont.getNormals("faded_screen"));
		newEntity1.assign<PolyName>("faded_screen3"); //just for render to let know what texture 
		newEntity1.assign<Transform>(sf::Vector2f(0,0), 0);
		VertexArray::Handle txtToRender = newEntity1.component<VertexArray>();

		//newEntity2.assign<RoundrectComp>(buttonn[0].rect, buttonn[0].text);
	//	newEntity2.assign<PolyName>("");
	//	newEntity2.assign<Transform>(sf::Vector2f(8, 5), 0);
	}
}

game_over_system::~game_over_system()
{
}
