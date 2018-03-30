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
    std::string partnames[5] = { "large eng.", "small eng.", "langing legs", "crane", "gun" };
	std::string garageNames[4] = { "1 garage", "2 garage" ,"3 garage" ,"4 garage" };
    int bodyposition = 500;
    int partposition = 150;
	int garagePositionY = 130;
    auto &container = ResourcesManager::getInstanceRef().vertCont;
    std::string bodys[3] = {
        "ALIEN_BODY",
        "LONG_BODY",
        "COBRA_BODY"
	};

	std::string parts[4] = {
		"large_engine",
		"small_engine",
		//"landing_legs",
		"crane",
		"gun"
    };

    for(int i=0; i<3; ++i)
    {
        bodybuttons[i].init(sf::Vector2f(bodyposition,50), bodynames[i], resource.font, bodys[i]);
        bodyposition += 120;
    }

    for(int i=0; i<4; ++i)
    {
        partbuttons[i].init(sf::Vector2f(1200,partposition), partnames[i], resource.font, parts[i]);
        partposition += 120;
		partbuttons[i].setTextureScale(90, 90);
    }
	for (int i = 0; i < 4; ++i)
	{
		garageButtons[i].init(sf::Vector2f(100, garagePositionY), garageNames[i], resource.font, bodys[3]);
		garagePositionY += 110;
	}

    start_button.init(resource.font,32, sf::Vector2f(150,670),sf::Color::White, "START", sf::Vector2f(40,15));
    save_button.init(resource.font,32, sf::Vector2f(150,600),sf::Color::White, "SAVE", sf::Vector2f(40,15));

    manager.init();

    return true;
}

void CreatorStage::input(sf::Event &event)
{
	start_button.rect.setOutlineThickness(8);
	save_button.rect.setOutlineThickness(8);

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
            if(!manager.is_body_set())
                return;

            manager.saveShip(ResourcesManager::getInstanceRef().shipInfo);
            next = &(ResourcesManager::getInstanceRef().gameplay_stage);
            fade_out = true;
            fade_in = false;
        }
    }
	// loading things to garage
	for (int i = 0; i < 4; ++i)
	{
		if (garageButtons[i].input(event))
		{
			std::cout << i + 1 << "  =  numer statku!" << std::endl;
			std::string & str = (ResourcesManager::getInstanceRef().shipInfo);
			
			str = "resources/levelData/ship_" + std::to_string(i + 1) + ".cfg";
			
			manager.loadPartFromFile(str);
			
		}
	}
	//
    for(int i=0; i<3; ++i)
        if(bodybuttons[i].input(event) && manager.parts.size() < 1)
           manager.set_body(bodybuttons[i].getName());
    for(int i=0; i<4; ++i)
        if(partbuttons[i].input(event))
           manager.add_part(partbuttons[i].getName());

    if(start_button.input(event))
    {
        if(!manager.is_body_set())
            return;

      manager.saveShip(ResourcesManager::getInstanceRef().shipInfo);
        next = &(ResourcesManager::getInstanceRef().gameplay_stage);
        fade_out = true;
        fade_in = false;
    }

    if(save_button.input(event))
        manager.saveShip(ResourcesManager::getInstanceRef().shipInfo);

    manager.input(event);
}

bool CreatorStage::update(float dt)
{
	if(fade_in)
    {
        sf::Color col = mask_rect.getFillColor();
        col.a = timer * 255.0f;
        mask_rect.setFillColor(col);
        timer -= dt;
        fade_in = (timer >=0);
    }

    if(fade_out)
    {
        sf::Color col = mask_rect.getFillColor();
        col.a = timer * 255.0f;
        mask_rect.setFillColor(col);
        timer += dt;
        fade_out = (timer < 1.f);
    }

    if(next && !fade_out)
        next->set();

    for(int i=0; i<3; ++i)
        bodybuttons[i].update(dt);
    for(int i=0; i<4; ++i)
        partbuttons[i].update(dt);
	for (int i = 0; i<4; ++i)
		garageButtons[i].update(dt);

    return true;
}

void CreatorStage::render(sf::RenderWindow &window)
{
    window.clear(sf::Color(30, 30, 30, 255));
    window.draw(esc_text);

    for(int i=0; i<3; ++i)
        window.draw(bodybuttons[i]);
    for(int i=0; i<4; ++i)
        window.draw(partbuttons[i]);
	for (int i = 0; i < 4; ++i)
		window.draw(garageButtons[i]);

    window.draw(start_button);
    window.draw(save_button);
    window.draw(manager);
    window.draw(mask_rect);
}

void CreatorStage::release()
{
    next = nullptr;
    for(int i=0; i<3; ++i)
        bodybuttons[i].release();
    for(int i=0; i<4; ++i)
        partbuttons[i].release();
	for (int i = 0; i < 4; ++i)
		garageButtons[i].release();

    start_button.release();
    save_button.release();
    manager.release();

    esc_text = sf::Text();
}
