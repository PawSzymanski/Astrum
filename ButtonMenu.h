#pragma once
#include "LibsAndDeclarations.h"


class ButtonMenu
{
	
public:
	int number, lenght;
	sf::Text text;
	RoundRect rect;

	ButtonMenu(int);
	~ButtonMenu();

	void init(sf::Font &font, int chSize, sf::Vector2f position, sf::Color color, std::string string, sf::Vector2f origin);
};

