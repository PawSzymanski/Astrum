/*
 *  lvlsetstage.cpp
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski
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

    auto & resource = ResourcesManager::getInstanceRef();

    button[0].init(sf::Vector2f(1450,600/2), 1, "ship repair", resource.font);
    button[1].init(sf::Vector2f(1450,600/2), 2, "supply run", resource.font);
    button[2].init(sf::Vector2f(1450,600/2), 3, "bomb drop", resource.font);

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
    high_nr= (high_nr<0)? 2:high_nr;
    high_nr= (high_nr>2)? 0:high_nr;

    for(int i=0; i<3; ++i)
    {
        button[i].highlighted = (i==high_nr);
    }

    for(int i=0; i<3; ++i)
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
    if(slide_in)
    {
        sf::Color col = esc_text.getFillColor();
        col.a = (timer * 255.0f > 255.0f)? 255 : timer*255.0f;
        esc_text.setFillColor(col);
        timer = ((timer + dt/2) > 1.0f)? 1.0f: (timer + dt/2);
                ;
        float pos_x[3] =  {430, 630, 830};
            bool in_pos = true;
        for(int i=0; i<3; ++i)
        {
            sf::Vector2f pos = button[i].getPosition();
            float dp = pos.x - pos_x[i] ;
			
            if(dp > 5)
            {
                button[i].setPosition(pos + sf::Vector2f(-dp/50,0));
                in_pos = false;
            }
        }

        slide_in = !in_pos;
    }
    if(slide_out)
    {
        sf::Color col = esc_text.getFillColor();
        col.a = (timer * 255.0f < 0.0f)? 0 : timer*255.0f;
        esc_text.setFillColor(col);
        timer = ((timer - dt/2) < 0.0f)? 0 : (timer - dt/2);

        float pos_x[3] = { -700,-950,-1200 };
        bool in_pos = true;
        for(int i=0; i<3; ++i)
        {
            sf::Vector2f pos = button[i].getPosition();
            float dp = pos.x + pos_x[i] ;
			//std::cout << "DP: " << dp << std::endl;

            if(dp > -2000)
            {
                button[i].setPosition(pos - sf::Vector2f(-dp/50,0));
                in_pos = false;
            }
        }

        slide_out = !in_pos;
    }
	if (slide_out_to_menu)
	{
		sf::Color col = esc_text.getFillColor();
		col.a = (timer * 255.0f < 0.0f) ? 0 : timer*255.0f;
		esc_text.setFillColor(col);
		timer = ((timer - dt / 2) < 0.0f) ? 0 : (timer - dt / 2);

		float pos_x[3] = { -700,-950,-1200 };
		bool in_pos = true;
		for (int i = 0; i<3; ++i)
		{
			sf::Vector2f pos = button[i].getPosition();
			float dp = pos.x - pos_x[i];
			//std::cout << "DP: " << dp << std::endl;

			if (dp < 2600)
			{
				button[i].setPosition(pos - sf::Vector2f(-dp / 50, 0));
				in_pos = false;
			}
		}

		slide_out_to_menu = !in_pos;
	}

    if(next_stage && !slide_out && !slide_out_to_menu)
        next_stage->set();

    return true;
}

void LvlSetStage::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    for(int i=0; i<3; ++i)
        window.draw(button[i]);
    window.draw(esc_text);
}

void LvlSetStage::release()
{
    esc_text = sf::Text();
    next_stage = nullptr;
    for(int i=0; i<3; ++i)
        button[i].release();
}
