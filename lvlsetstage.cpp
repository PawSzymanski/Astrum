/*
 *  lvlsetstage.cpp
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski ~ Modified by Pawe³ Szymañski
 */

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
    next_stage = nullptr;
    timer = 0;

	speed = 30.0;

	numberOfLevels = 4; //SET NUMBER OF LEVELS IF ANY ADDED

    auto & resource = ResourcesManager::getInstanceRef();

    button[0].init(sf::Vector2f(1450,600/2), 1, "ship repair", resource.font);
    button[1].init(sf::Vector2f(1650,600/2), 2, "supply run", resource.font);
    button[2].init(sf::Vector2f(1850,600/2), 3, "bomb drop", resource.font);
	button[3].init(sf::Vector2f(2050,600/2), 4, "bomb drop 2", resource.font);

    slide_in = true;
    slide_out = false;

    esc_text.setCharacterSize(32);
    esc_text.setFillColor(sf::Color::White);
    esc_text.setPosition(50,50);
    esc_text.setFont(resource.font);
    esc_text.setString("Menu:  ESC");

    ships[0] = "resources/levelData/ship_1.cfg";
    ships[1] = "resources/levelData/ship_2.cfg";
    ships[2] = "resources/levelData/ship_3.cfg";

    levels[0] = "resources/levelData/level_1.cfg";
    levels[1] = "resources/levelData/level_2.cfg";
    levels[2] = "resources/levelData/level_3.cfg";
	levels[3] = "resources/levelData/level_4.cfg";

    return true;
}

void LvlSetStage::input(sf::Event &event)
{
    static int high_nr = 0;

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            next_stage = &(ResourcesManager::getInstanceRef().menu_stage);
            slide_out_to_menu = true;
        }
        else if( event.key.code == sf::Keyboard::Left)
        {
            std::cout<<"left"<<std::endl;
            high_nr--;
        }
        else if( event.key.code == sf::Keyboard::Right)
        {
            std::cout<<"right"<<std::endl;
            high_nr++;
        }
    }
    high_nr= (high_nr<0)? (numberOfLevels -1):high_nr;
    high_nr= (high_nr>numberOfLevels-1)? 0:high_nr;

    for(int i=0; i<	numberOfLevels; ++i)
    {
        button[i].highlighted = (i==high_nr);
    }

    for(int i=0; i<numberOfLevels; ++i)
        if(button[i].input(event))
        {
            ResourcesManager::getInstanceRef().levelInfo = levels[i];
            ResourcesManager::getInstanceRef().shipInfo = ships[i];
            slide_out = true;
            next_stage = &(ResourcesManager::getInstanceRef().creator_stage);
        }
}

bool LvlSetStage::update(float dt)
{
	//std::cout << "X: " << button[0].getPosition().x <<"slide_in: "<< slide_in << "slide_out: "<< slide_out << "slide_out_to_menu: "<< slide_out_to_menu<< std::endl;

    if(slide_in)
    {
		speed -= 0.4;

		for (int i = 0; i < numberOfLevels; ++i)
		{
			button[i].setPosition(button[i].getPosition() - sf::Vector2f(speed, 0));
		}

		if (speed < 0)
		{
			slide_in = false;
		}
    }
    if(slide_out)
    {
		speed += 0.4;

		for (int i = 0; i < numberOfLevels; ++i)
		{
			button[i].setPosition(button[i].getPosition() - sf::Vector2f(speed, 0));
		}

		if (button[numberOfLevels - 1].getPosition().x < -100)
		{
			slide_out = false;
		}
    }
	if (slide_out_to_menu)
	{
		speed -= 1;

		for (int i = 0; i < numberOfLevels; ++i)
		{
			button[i].setPosition(button[i].getPosition() - sf::Vector2f(speed, 0));
		}

		if (button[0].getPosition().x > ResourcesManager::getInstanceRef().window.getSize().x)
		{
			slide_out_to_menu = false;
		}
	}

    if(next_stage && !slide_out && !slide_out_to_menu)
        next_stage->set();

    return true;
}

void LvlSetStage::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    for(int i=0; i<numberOfLevels; ++i)
        window.draw(button[i]);
    window.draw(esc_text);
}

void LvlSetStage::release()
{
    esc_text = sf::Text();
    next_stage = nullptr;
    for(int i=0; i<numberOfLevels; ++i)
        button[i].release();
}
