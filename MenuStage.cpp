/*
*
*
* Pawe³ Szymañski
*/
#include "MenuStage.h"
#include "ResourceManager.h"


MenuStage::MenuStage() : actionCode(0), startButton(0), optionsButton(1), exitButton(2), isPressed(0), buttonSpeed(0.0f), isSliding(0)
{

}

MenuStage::~MenuStage()
{
	release();
}


void MenuStage::animationsUpdate()
{
	std::uniform_int_distribution<int> d(-1, 1);
	std::random_device rd1;

	for (auto &anim : animVec)
	{
		if (anim.spr.getPosition().x < -150)
		{
			anim.x = 1;
			anim.y = d(rd1);
			anim.rot = 90 + anim.y*45;
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

bool MenuStage::init()
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


	font = ResourcesManager::getInstanceRef().font; 

	startButton.init(font, 40, sf::Vector2f(0, 0), sf::Color::White, "Single", sf::Vector2f(40, 20));
	startButton.rect.setOutlineThickness(12);
	optionsButton.init(font, 40, sf::Vector2f(0, 0), sf::Color::White, "Options", sf::Vector2f(60, 20));
	exitButton.init(font, 40, sf::Vector2f(0, 0), sf::Color::White, "Exit", sf::Vector2f(30, 20));
	multiButton.init(font, 40, sf::Vector2f(0, 0), sf::Color::White, "Multi", sf::Vector2f(35, 20));
	
	if (isSliding == 2)
	{
		buttonSpeed = 2100;
	}
	return true;
}

void MenuStage::slidingRight(float dt)
{
	if (startButton.rect.getPosition().x > -100)
	{
		buttonSpeed += 30;
		startButton.rect.setPosition(startButton.rect.getPosition().x - buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 6.9);
		startButton.text.setPosition(startButton.text.getPosition().x - buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 6.9);

		multiButton.rect.setPosition(optionsButton.rect.getPosition().x - buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 21);
		multiButton.text.setPosition(optionsButton.text.getPosition().x - buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 21);

		optionsButton.rect.setPosition(optionsButton.rect.getPosition().x - buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 21);
		optionsButton.text.setPosition(optionsButton.text.getPosition().x - buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 21);

		exitButton.rect.setPosition(exitButton.rect.getPosition().x - buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 6.9);
		exitButton.text.setPosition(exitButton.text.getPosition().x - buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 6.9);
	}
	else {
		this->isSliding = 0;
	}
}

void MenuStage::slidingLeft(float dt)
{
	if (startButton.rect.getPosition().x < windowSize.x / 2)
	{
		buttonSpeed -= 30;

		startButton.rect.setPosition(startButton.rect.getPosition().x + buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 6.9);
		startButton.text.setPosition(startButton.text.getPosition().x + buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 6.9);
		
		multiButton.rect.setPosition(optionsButton.rect.getPosition().x + buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 21);
		multiButton.text.setPosition(optionsButton.text.getPosition().x + buttonSpeed*dt, windowSize.y / 2 - windowSize.y / 21);

		optionsButton.rect.setPosition(optionsButton.rect.getPosition().x + buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 21);
		optionsButton.text.setPosition(optionsButton.text.getPosition().x + buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 21);

		exitButton.rect.setPosition(exitButton.rect.getPosition().x + buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 6.9);
		exitButton.text.setPosition(exitButton.text.getPosition().x + buttonSpeed*dt, windowSize.y / 2 + windowSize.y / 6.9);
	}
	else {
		isSliding = 0;
	}
}

bool MenuStage::update(float dt)
{
	auto &resources_manager = ResourcesManager::getInstanceRef();

	if (isSliding == 1)
	{
		slidingRight(dt);
	}
	else if (isSliding == 2)
	{
		slidingLeft(dt);
	}
	else if(isPressed)
	{
		isPressed = 0;
		buttonSpeed = 0.0f;
		if (actionCode == 0)
		{
			this->isSliding = 2;
			resources_manager.lvl_set_stage.set();
		}
		else if (actionCode == 1)
		{
			this->isSliding = 2;
			resources_manager.login_stage.set();
		}
		else if (actionCode == 2)
		{
			//this->isSliding = 2;
			//resources_manager.gameplay_stage.set();
		}
		else if (actionCode == 3)
		{
			this->isSliding = 2;
			resources_manager.exit_stage.set();
		}
	}
	else
	{
		startButton.text.setPosition(windowSize.x / 2, windowSize.y / 2 - windowSize.y / 6.9);
		startButton.rect.setPosition(windowSize.x / 2, windowSize.y / 2 - windowSize.y / 6.9);
		multiButton.text.setPosition(windowSize.x / 2, windowSize.y / 2 - windowSize.y / 21);
		multiButton.rect.setPosition(windowSize.x / 2, windowSize.y / 2 - windowSize.y / 21);
		optionsButton.text.setPosition(windowSize.x / 2, windowSize.y / 2 + windowSize.y / 21);
		optionsButton.rect.setPosition(windowSize.x / 2, windowSize.y / 2 + windowSize.y / 21);
		exitButton.text.setPosition(windowSize.x / 2, windowSize.y / 2 + windowSize.y / 6.9);
		exitButton.rect.setPosition(windowSize.x / 2, windowSize.y / 2 + windowSize.y / 6.9);
	}
	animationsUpdate();
	return true;
}

void MenuStage::render(sf::RenderWindow &window)
{
	windowSize = window.getSize();
	//window.clear(sf::Color(30, 30, 30, 255));
	window.draw(backGroundSprite);

	for (auto spr : animVec)
		window.draw(spr.spr);
	
	window.draw(startButton.text);
	window.draw(startButton.rect);

	window.draw(multiButton.text);
	window.draw(multiButton.rect);

	window.draw(optionsButton.text);
	window.draw(optionsButton.rect);

	window.draw(exitButton.text);
	window.draw(exitButton.rect);


}

void MenuStage::release()
{
    startButton.text = sf::Text();
	multiButton.text = sf::Text();
    optionsButton.text = sf::Text();
    exitButton.text = sf::Text();

	backGroundSprite = sf::Sprite();

	for (auto &a : animVec)
	{
		a.spr = sf::Sprite();
	}
	for (auto &t : shipTexture)
	{
		t = sf::Texture();
	}
}

void MenuStage::showBar()
{
	if (actionCode == 0)
	{
		startButton.rect.setOutlineThickness(12);
	}
	else if (actionCode == 1)
	{
		multiButton.rect.setOutlineThickness(12);
	}
	else if (actionCode == 2)
	{
		optionsButton.rect.setOutlineThickness(12);
	}
	else if (actionCode == 3)
	{
		exitButton.rect.setOutlineThickness(12);
	}
}

void MenuStage::input(sf::Event & event)
{
	auto &resources_manager = ResourcesManager::getInstanceRef();
	
	startButton.rect.setOutlineThickness(8);
	multiButton.rect.setOutlineThickness(8);
	optionsButton.rect.setOutlineThickness(8);
	exitButton.rect.setOutlineThickness(8);
	showBar();

	if (startButton.input(event))
	{
		actionCode = 0;
		showBar();
	}
	else if (multiButton.input(event))
	{
		actionCode = 1;
		showBar();
	}
	else if (optionsButton.input(event))
	{
		actionCode = 2;
		showBar();
	}
	else if (exitButton.input(event))
	{
		actionCode = 3;
		showBar();
	}

	if (event.type == sf::Event::KeyPressed)
	{
		
		//reset bar
		

		if (event.key.code == sf::Keyboard::Escape)
		{
			resources_manager.exit_stage.set();
		}
		else if (event.key.code == sf::Keyboard::Up)
		{
			if (actionCode != 0)
				--actionCode;
			else
			actionCode = 2;

			showBar();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			if (actionCode != 3)
				++actionCode;
			else
			actionCode = 0;

			showBar();
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			isPressed = 1;
			isSliding = 1;
		}
	}
	if (event.type == sf::Event::MouseButtonReleased && (startButton.input(event) || multiButton.input(event) ||  optionsButton.input(event) || exitButton.input(event) ))
	{
		if (event.key.code == sf::Mouse::Left)
		{
			isPressed = true;

			isSliding = 1;
		}
	}

}
