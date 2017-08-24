#pragma once
#include "LibsAndDeclarations.h"


class ButtonMenu : public sf::Drawable
{
   
public:
	bool has_mouse;
	int number, lenght;
	sf::Text text;
	RoundRect rect;

    ButtonMenu();
	ButtonMenu(int);
	~ButtonMenu();

	void init(sf::Font &font, int chSize, sf::Vector2f position, sf::Color color, std::string string, sf::Vector2f origin);
    bool input(sf::Event & ev);
    void release();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

