#include "MenuStage.h"
#include "ResourceManager.h"

MenuStage::MenuStage() : actionCode(0), rect(sf::Vector2f(3, 2), 1.0f)
{
}

MenuStage::~MenuStage()
{
	release();
}

bool MenuStage::init()
{
	if (!font.loadFromFile("resources/sansation.ttf"))
		return false;

	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(0.5);

	start_message.setFont(font);
	start_message.setCharacterSize(40);
	start_message.setPosition(170.f, 150.f);
	start_message.setFillColor(sf::Color::White);
	start_message.setString("Start");
	start_message.setOrigin(40, 20);
	
	options_message.setFont(font);
	options_message.setCharacterSize(40);
	options_message.setPosition(170.f, 150.f);
	options_message.setFillColor(sf::Color::White);
	options_message.setString("Options");
	options_message.setOrigin(60,20);

	exit_message.setFont(font);
	exit_message.setCharacterSize(40);
	exit_message.setPosition(170.f, 150.f);
	exit_message.setFillColor(sf::Color::White);
	exit_message.setString("Exit");
	exit_message.setOrigin(30, 20);

	return true;
}

bool MenuStage::update(float dt)
{

	return true;
}

void MenuStage::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(255, 0, 0));
	start_message.setPosition(window.getSize().x / 2, window.getSize().y / 2 - window.getSize().y / 10);
	window.draw(start_message);
	options_message.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.draw(options_message);
	exit_message.setPosition(window.getSize().x / 2, window.getSize().y / 2 + window.getSize().y / 10);
	window.draw(exit_message);
}

void MenuStage::release()
{
	//message = sf::Text();
	font = sf::Font();
}

void MenuStage::returnFun()
{
	auto &resources_manager = ResourcesManager::getInstanceRef();

	if (actionCode == 0)
	{
		resources_manager.gameplay_stage.set();
	}
	else if (actionCode == 1)
	{
		resources_manager.gameplay_stage.set();
	}
	else if (actionCode == 2)
	{
		resources_manager.exit_stage.set();
	}
}

void MenuStage::showBar()
{

}


void MenuStage::eventsManage(sf::Event & event)
{
	auto &resources_manager = ResourcesManager::getInstanceRef();
	
	if (event.type == sf::Event::KeyPressed)
	{
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
			if (actionCode != 2)
				++actionCode;
			else
			actionCode = 0;
			showBar();
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			returnFun();
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			returnFun();
		}
	}

}
