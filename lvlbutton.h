/*
 *  lvlbutton.h
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski
 */

#ifndef LVLBUTTON_H
#define LVLBUTTON_H

#include "LibsAndDeclarations.h"
#include <sstream>

class LvlButton : public sf::Drawable
{
	bool has_mouse;
	bool clicked;

    sf::Text num, text;
    RoundRect rect;
	sf::Vector2f pos;
public:
    bool highlighted;

public:
    LvlButton();

	bool input(sf::Event & ev);

    void init(sf::Vector2f pos, int num, std::string text, sf::Font & font);
    void setPosition(const sf::Vector2f& pos);
	void release();
   
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f getPosition();
};

#endif // LVLBUTTON_H
