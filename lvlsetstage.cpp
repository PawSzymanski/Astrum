/*
 *  lvlsetstage.cpp
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski ~ Modified by Pawe³ Szymañski
 */

#include "lvlsetstage.h"
#include "ResourceManager.h"

LvlSetStage::LvlSetStage() : wasLastXMouse(false)
{

}

LvlSetStage::~LvlSetStage()
{

}

bool LvlSetStage::init()
{
	backGroundSprite.setTexture(ResourcesManager::getInstanceRef().textureCont.getTexture("back_ground1"));
	backGroundSprite.setPosition(sf::Vector2f(-50, -50));


	shipTexture[0] = ResourcesManager::getInstanceRef().textureCont.getTexture("COBRA_BODY");
	sf::Sprite spr;
	spr.setTexture(shipTexture[0]);
	spr.setPosition(sf::Vector2f(-160, 100));
	spr.setOrigin(260.5, 373);
	spr.setScale(0.2, 0.2);
	aniamtion anim(spr);
	animVec.push_back(anim);

	shipTexture[1] = ResourcesManager::getInstanceRef().textureCont.getTexture("ALIEN_BODY");
	sf::Sprite spr1;
	spr1.setTexture(shipTexture[1]);
	spr1.setPosition(sf::Vector2f(200, -160));
	spr1.setOrigin(260.5, 373);
	spr1.setScale(0.15, 0.15);
	aniamtion anim2(spr1);
	animVec.push_back(anim2);

	shipTexture[2] = ResourcesManager::getInstanceRef().textureCont.getTexture("LONG_BODY");
	sf::Sprite spr2;
	spr2.setTexture(shipTexture[2]);
	spr2.setPosition(sf::Vector2f(-170, -100));
	spr2.setOrigin(260.5, 373);
	spr2.setScale(0.1, 0.1);

	aniamtion anim3(spr2);
	animVec.push_back(anim3);


    next_stage = nullptr;
    timer = 0;

	speed = 30.0;

	numberOfLevels = 5; //SET NUMBER OF LEVELS IF ANY ADDED

    auto & resource = ResourcesManager::getInstanceRef();

    button[0].init(sf::Vector2f(1450,600/2), 1, "ship repair", resource.font);
    button[1].init(sf::Vector2f(1650,600/2), 2, "supply run", resource.font);
    button[2].init(sf::Vector2f(1850,600/2), 3, "shooting adept", resource.font);
	button[3].init(sf::Vector2f(2050,600/2), 4, "bomb drop 2", resource.font);
	button[4].init(sf::Vector2f(2250, 600 / 2), 5, "first real case", resource.font);

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
	levels[4] = "resources/levelData/level_5.cfg";

    return true;
}

void LvlSetStage::input(sf::Event &event)
{
    static int high_nr = 0;

	if (event.type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << event.mouseMove.x << std::endl;
			float xMove = event.mouseMove.x;
			if (!wasLastXMouse)
			{
				lastXMouse = event.mouseMove.x;
				wasLastXMouse = true;
			}
			else
			{
				int boolHelper = 1;
				if ((button[numberOfLevels - 1].getPosition().x < 500 && lastXMouse - event.mouseMove.x >0) || 
					(button[0].getPosition().x > 1000 && lastXMouse - event.mouseMove.x <0))
				{
					boolHelper = -1;
				}

				wasLastXMouse = false;
				for (int i = 0; i < numberOfLevels; ++i)
				{
					button[i].setPosition(button[i].getPosition() - sf::Vector2f((lastXMouse - event.mouseMove.x)*2* boolHelper, 0));
				}
			}
		}
	}
	else
	{
		wasLastXMouse = false;
	}

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

	animationsUpdate();
    return true;
}

void LvlSetStage::animationsUpdate()
{
	std::uniform_int_distribution<int> d(-1, 1);
	std::random_device rd1;

	for (auto &anim : animVec)
	{
		if (anim.spr.getPosition().x < -150)
		{
			anim.x = 1;
			anim.y = d(rd1);
			anim.rot = 90 + anim.y * 45;
			anim.spr.setPosition(anim.spr.getPosition().x + anim.x, anim.spr.getPosition().y + anim.y);
			anim.spr.setRotation(anim.rot);
		}
		else if (anim.spr.getPosition().x > windowSize.x + 150)
		{
			anim.x = -1;
			anim.y = d(rd1);
			anim.rot = 270 + -anim.y * 45;
			anim.spr.setPosition(anim.spr.getPosition().x + anim.x, anim.spr.getPosition().y + anim.y);
			anim.spr.setRotation(anim.rot);
		}
		if (anim.spr.getPosition().y < -150)
		{
			anim.x = d(rd1);
			anim.y = 1;
			anim.rot = 180 + -anim.x * 45;
			anim.spr.setPosition(anim.spr.getPosition().x + anim.x, anim.spr.getPosition().y + anim.y);
			anim.spr.setRotation(anim.rot);
		}
		else if (anim.spr.getPosition().y > windowSize.y + 150)
		{
			anim.x = d(rd1);
			anim.y = -1;
			anim.rot = 0 + anim.x * 45;
			anim.spr.setPosition(anim.spr.getPosition().x + anim.x, anim.spr.getPosition().y + anim.y);
			anim.spr.setRotation(anim.rot);
		}
		else
		{
			anim.spr.setPosition(anim.spr.getPosition().x + anim.x, anim.spr.getPosition().y + anim.y);
			anim.spr.setRotation(anim.rot);
		}
	}
}


void LvlSetStage::render(sf::RenderWindow &window)
{
	windowSize = window.getSize();
	//window.clear(sf::Color(30, 30, 30, 255));
	window.draw(backGroundSprite);

	for (auto spr : animVec)
		window.draw(spr.spr);

  
    for(int i=0; i<numberOfLevels; ++i)
        window.draw(button[i]);
    window.draw(esc_text);
}

void LvlSetStage::release()
{
	backGroundSprite = sf::Sprite();

    esc_text = sf::Text();

	for (auto &a : animVec)
	{
		a.spr = sf::Sprite();
	}
	for (auto &t : shipTexture)
	{
		t = sf::Texture();
	}

    next_stage = nullptr;
    for(int i=0; i<numberOfLevels; ++i)
        button[i].release();
}
