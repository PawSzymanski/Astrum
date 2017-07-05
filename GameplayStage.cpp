#include "GameplayStage.h"

GameplayStage::GameplayStage()
{
}

GameplayStage::~GameplayStage()
{
	release();
}

void GameplayStage::updateCamera()
{
}

bool GameplayStage::init()
{
	camera.reset(sf::FloatRect(0, 0, 17.5, 10));

	return true;
}

bool GameplayStage::update(float dt)
{
	updateCamera();

	//if (ecs_gameplay_ptr->update(dt)) return true;

	return true;
}

void GameplayStage::draw(sf::RenderWindow &window)
{
	window.setView(camera);
	window.clear(sf::Color(0, 255, 0));

	//ecs_gameplay_ptr->draw(window);

	window.setView(window.getDefaultView());
}

void GameplayStage::release()
{
	//ecs_gameplay_ptr.reset();
}

void GameplayStage::eventsManage(sf::Event & event)
{
}
