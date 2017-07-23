#include "ButtonMenu.h"



ButtonMenu::ButtonMenu()
    :number(0)
{

}

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

    rect.setPosition(position);
	rect.corner_radius = 10;
	rect.size = sf::Vector2f(150, chSize / 2+5); 
	rect.setOrigin(65, 5);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(8);

}

bool ButtonMenu::input(sf::Event &ev)
{

   // std::cout<<"hasmouse "<< has_mouse<<std::endl;
  //  rect.setOutlineThickness((has_mouse)? 15 : 8);
	if (has_mouse)
	{
		rect.setOutlineThickness(15);
	}


    if(ev.type == sf::Event::MouseMoved)
    {
        has_mouse = (ev.mouseMove.x > rect.getPosition().x - 80 && ev.mouseMove.x < rect.getPosition().x + 80 &&
                ev.mouseMove.y > rect.getPosition().y - 20 && ev.mouseMove.y < rect.getPosition().y + 40);
    }
    else if(ev.type == sf::Event::MouseButtonReleased && has_mouse)
        return true;

    return false;
}

void ButtonMenu::release()
{
    text = sf::Text();
    has_mouse = 0;
    number = 0;
    lenght = 0;
    rect = RoundRect();
}

void ButtonMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect);
    target.draw(text);
}


ButtonMenu::~ButtonMenu()
{
}
