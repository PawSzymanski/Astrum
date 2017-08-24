#include "ExitStage.h"

ExitStage::ExitStage() : timer(0.f)
{
}

ExitStage::~ExitStage()
{
}

bool ExitStage::init()
{
	timer = 0.f;
	std::cout << "Exit..." << std::endl;
	return true;
}

bool ExitStage::update(float dt)
{
	timer += dt;
	if (timer >= 1.f)
	{
		timer = 0.f;
		return false;
	}

	return true;
}

void ExitStage::render(sf::RenderWindow & window)
{
    float c = 255.0f - (timer * 255.0f);
    window.clear(sf::Color(c,c,c));
}

void ExitStage::release()
{
}

void ExitStage::input(sf::Event & event)
{
}
