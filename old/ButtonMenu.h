#pragma once
#include "LibsAndDeclarations.h"


class ButtonMenu : public sf::Drawable
{
    bool has_mouse;
public:
	int lenght;
	sf::Text text;
	RoundRect rect;

    ButtonMenu();
	~ButtonMenu();

	void init(sf::Font &font, int chSize, sf::Vector2f position, sf::Color color, std::string string, sf::Vector2f origin);
    bool input(sf::Event & ev);
    void release();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

