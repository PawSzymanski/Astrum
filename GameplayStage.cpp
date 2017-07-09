#include "GameplayStage.h"
#include "ResourceManager.h"

GameplayStage::GameplayStage()
{
}

GameplayStage::~GameplayStage()
{
	release();
}

void GameplayStage::updateCamera()
{
	//camera.reset(sf::FloatRect(0, 0, 17.5, 10));
}

bool GameplayStage::init()
{

	auto &ex = ResourcesManager::getInstanceRef().ex;
	auto &window = ResourcesManager::getInstanceRef().window;
	camera.reset(sf::FloatRect(0, 0, 17.5, 10));

	ex.systems.update<player_input_system>(dtime);
	return true;
}

bool GameplayStage::update(float dt)
{
	dtime = dt;
	auto &ex = ResourcesManager::getInstanceRef().ex;
	auto &phisics = ResourcesManager::getInstanceRef().phisics;
	updateCamera();

	//if (ecs_gameplay_ptr->update(dt)) return true;

	
	phisics.update(dt);
	ex.systems.update<engine_system>(dt);
	
    //render

	
	return true;
}

void GameplayStage::render(sf::RenderWindow &window)
{
	auto &ex = ResourcesManager::getInstanceRef().ex;
	window.setView(camera);
	ex.systems.update<render_system>(dtime);
}

void GameplayStage::release()
{

}

void GameplayStage::input(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        ResourcesManager::getInstanceRef().lvl_set_stage.set();
}
