#include "lvlsetstage.h"
#include "ResourceManager.h"

LvlSetStage::LvlSetStage()
{

}

LvlSetStage::~LvlSetStage()
{

}

bool LvlSetStage::init()
{

}

void LvlSetStage::input(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        ResourcesManager::getInstanceRef().menu_stage.set();
}

bool LvlSetStage::update(float dt)
{
    return true;
}

void LvlSetStage::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
}

void LvlSetStage::release()
{

}
