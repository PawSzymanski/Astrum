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

    next = nullptr;
    current_body = nullptr;

    body_transform.translate(650, 500);
    body_transform.scale(200,200);

    esc_text.setCharacterSize(32);
    esc_text.setFillColor(sf::Color::White);
    esc_text.setPosition(50,50);
    esc_text.setFont(resource.font);
    esc_text.setString("Lvl set:  ESC");

    mask_rect.setFillColor(sf::Color::Black);
    mask_rect.setPosition(sf::Vector2f(0,0));
    mask_rect.setSize(sf::Vector2f(1400,800));

    fade_in = true;
    fade_out = false;
    timer = 1.0f;

    std::string bodynames[3] = { "Mk. I" , "Mk. II", "Mk. III" };
    std::string partnames[4] = { "large eng.", "small eng.", "langing legs", "crane" };
    int bodyposition = 500;
    int partposition = 200;
    auto &container = ResourcesManager::getInstanceRef().vertCont;
    std::string bodys[3] ={
        "TRIANGLE_BODY",
        "LONG_BODY",
        "COBRA_BODY"};

    for(int i=0; i<3; ++i)
    {
        bodybuttons[i].init(sf::Vector2f(bodyposition,50), bodynames[i], resource.font, bodys[i]);
        bodyposition += 120;
    }

    for(int i=0; i<4; ++i)
    {
        partbuttons[i].init(sf::Vector2f(1200,partposition), partnames[i], resource.font, bodys[1]);
        partposition += 120;
    }

    start_button.init(resource.font,32, sf::Vector2f(150,700),sf::Color::White, "START", sf::Vector2f(40,15));

    return true;
}

void CreatorStage::input(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            next = &(ResourcesManager::getInstanceRef().lvl_set_stage);
            fade_out = true;
            fade_in = false;
        }
        else if(event.key.code == sf::Keyboard::Return)
        {
            next = &(ResourcesManager::getInstanceRef().gameplay_stage);
            fade_out = true;
            fade_in = false;
        }
    }

    for(int i=0; i<3; ++i)
        if(bodybuttons[i].input(event))
            current_body = &(ResourcesManager::getInstanceRef().vertCont.getPoly(bodybuttons[i].getName()));
    for(int i=0; i<4; ++i)
        partbuttons[i].input(event);

    if(start_button.input(event))
    {
        next = &(ResourcesManager::getInstanceRef().gameplay_stage);
        fade_out = true;
    }

}

bool CreatorStage::update(float dt)
{
    if(fade_in)
    {
        sf::Color col = mask_rect.getFillColor();
        col.a = timer * 255.0f;
        mask_rect.setFillColor(col);
        timer -= dt/2;
        fade_in = (timer >=0);
    }

    if(fade_out)
    {
        sf::Color col = mask_rect.getFillColor();
        col.a = timer * 255.0f;
        mask_rect.setFillColor(col);
        timer += dt/2;
        fade_out = (timer < 1.f);
    }

    if(next && !fade_out)
        next->set();

    for(int i=0; i<3; ++i)
        bodybuttons[i].update(dt);
    for(int i=0; i<4; ++i)
        partbuttons[i].update(dt);

    //std::cout<<"fade_in "<<fade_in<<std::endl;
    //std::cout<<"fade_out "<<fade_out<<std::endl;
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

    if(current_body)
        window.draw(*current_body, body_transform);

    window.draw(start_button);
    window.draw(mask_rect);
}

void CreatorStage::release()
{
    next = nullptr;
    current_body = nullptr;
    body_transform = sf::Transform();
    for(int i=0; i<3; ++i)
        bodybuttons[i].release();
    for(int i=0; i<4; ++i)
        partbuttons[i].release();

    start_button.release();

    esc_text = sf::Text();
}
