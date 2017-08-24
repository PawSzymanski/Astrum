/*
 *  keyassigner.cpp
 *
 *  Created: 2017-07-10
 *   Author: Patryk Wojtanowski
 */

#include "keyassigner.h"

KeyAssigner::KeyAssigner()
    :part(nullptr)
{

}

void KeyAssigner::assign(Part *p)
{
    part = p;
}

void KeyAssigner::input(sf::Event &ev)
{
    if(part && ev.type == sf::Event::KeyPressed && ev.key.code < 27)
    {
        part->key = ev.key.code + 65;
        part = nullptr;
    }
}

void KeyAssigner::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(!part)
        return;

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0,0,0, 200));
    rect.setPosition(0,0);
    rect.setSize(sf::Vector2f(1400, 900));

    target.draw(rect);
    target.draw(*(part->v_array), part->trans);
}

void KeyAssigner::release()
{
    part = nullptr;
}
