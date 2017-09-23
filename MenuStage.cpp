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

bool MenuStage::init()
{
	font = ResourcesManager::getInstanceRef().font; 

	startButton.init(font, 40, sf::Vector2f(0, 0), sf::Color::White, "Start", sf::Vector2f(40, 20));
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
		std::cout << " x:" <<startButton.rect.getPosition().x << std::endl;
	}
	else {
		this->isSliding = 0;
	}
}
//ZROBIC PRZESUWANIE W LEWO
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

//DODAC SIEBIE JAKO AUTORA DO PLIKÓW !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
			this->isSliding = 2;
			resources_manager.gameplay_stage.set();
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
	return true;
}

void MenuStage::render(sf::RenderWindow &window)
{
	windowSize = window.getSize();
	window.clear(sf::Color(0, 0, 0));

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
