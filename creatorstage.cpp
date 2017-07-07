/*
 *  creatorstage.cpp
 *
 *  Created: 2017-07-07
 *   Author: Patryk Wojtanowski
 */

#include "creatorstage.h"
#include "ResourceManager.h"

CreatorStage::CreatorStage()
{

}

bool CreatorStage::init()
{
    auto& resource = ResourcesManager::getInstanceRef();

    esc_text.setCharacterSize(32);
    esc_text.setFillColor(sf::Color::White);
    esc_text.setPosition(50,50);
    esc_text.setFont(resource.font);
    esc_text.setString("Lvl set:  ESC");

    std::string bodynames[3] = { "body1" , "body2", "body3" };
    std::string partnames[4] = { "large eng.", "small eng.", "langing legs", "crane" };
    int bodyposition = 500;
    int partposition = 200;

    for(int i=0; i<3; ++i)
    {
        bodybuttons[i].init(sf::Vector2f(bodyposition,50), bodynames[i], resource.font);
        bodyposition += 120;
    }

    for(int i=0; i<4; ++i)
    {
        partbuttons[i].init(sf::Vector2f(1200,partposition), partnames[i], resource.font);
        partposition += 120;
    }

    start_button.init(resource.font,32, sf::Vector2f(150,700),sf::Color::White, "START", sf::Vector2f(40,15));

    return true;
}

void CreatorStage::input(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        ResourcesManager::getInstanceRef().lvl_set_stage.set();

    for(int i=0; i<3; ++i)
        bodybuttons[i].input(event);
    for(int i=0; i<4; ++i)
        partbuttons[i].input(event);

    if(start_button.input(event))
        ResourcesManager::getInstanceRef().gameplay_stage.set();

}

bool CreatorStage::update(float dt)
{
    return true;
}

void CreatorStage::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    window.draw(esc_text);

    for(int i=0; i<3; ++i)
        window.draw(bodybuttons[i]);
    for(int i=0; i<4; ++i)
        window.draw(partbuttons[i]);

    window.draw(start_button);
}

void CreatorStage::release()
{
    for(int i=0; i<3; ++i)
        bodybuttons[i].release();
    for(int i=0; i<4; ++i)
        partbuttons[i].release();

    start_button.release();

    esc_text = sf::Text();
}
