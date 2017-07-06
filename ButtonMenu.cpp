#include "ButtonMenu.h"



ButtonMenu::ButtonMenu(int number) : number (number)
{

}

void ButtonMenu::init(sf::Font &font, int chSize, sf::Vector2f position, sf::Color color, std::string string, sf::Vector2f origin) 
{
	text.setFont(font);
	text.setCharacterSize(chSize);
	text.setPosition(position);
	text.setFillColor(color);
	text.setString(string);
	text.setOrigin(origin);
	lenght = text.getCharacterSize()/3 * string.length();

	rect.corner_radius = 10;
	rect.size = sf::Vector2f(150, chSize / 2+5); 
	rect.setOrigin(65, 5);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(8);
	
}


ButtonMenu::~ButtonMenu()
{
}
