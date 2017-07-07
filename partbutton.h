/*
 *  partbutton.h
 *
 *  Created: 2017-07-07
 *   Author: Patryk Wojtanowski
 */

#ifndef PARTBUTTON_H
#define PARTBUTTON_H

#include "LibsAndDeclarations.h"

class PartButton : public sf::Drawable
{
    sf::Text text;
    RoundRect rect;
    sf::Vector2f pos;

    bool has_mouse;

public:
    PartButton();

    void init(sf::Vector2f pos, std::string text, sf::Font & font);
    bool input(sf::Event & ev);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void release();
};

#endif // PARTBUTTON_H
