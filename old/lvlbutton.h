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
    sf::Text num, text;
    RoundRect rect;
    sf::Vector2f pos;

    bool has_mouse;
    bool clicked;
public:
    bool highlighted;

public:
    LvlButton();

    void init(sf::Vector2f pos, int num, std::string text, sf::Font & font);
    bool input(sf::Event & ev);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void release();
};

#endif // LVLBUTTON_H
