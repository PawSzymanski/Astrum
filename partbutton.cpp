/*
 *  partbutton.cpp
 *
 *  Created: 2017-07-07
 *   Author: Patryk Wojtanowski
 */

#include "partbutton.h"

PartButton::PartButton()
{

}

void PartButton::init(sf::Vector2f pos, std::string text, sf::Font &font)
{
    this->pos = pos;
    rect.corner_radius = 6;
    rect.size = sf::Vector2f(60,60);
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(6);
    rect.setPosition(pos);

    this->text.setPosition(pos + sf::Vector2f(-10,70));
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(18);
    this->text.setFont(font);
    this->text.setString(text);
}

bool PartButton::input(sf::Event &ev)
{
    rect.setOutlineThickness((has_mouse)? 10 : 6);

    if(ev.type == sf::Event::MouseMoved)
    {
        has_mouse = (ev.mouseMove.x > pos.x && ev.mouseMove.x < pos.x + rect.size.x &&
                ev.mouseMove.y > pos.y && ev.mouseMove.y < pos.y + + rect.size.y);
    }
    else if(ev.type == sf::Event::MouseButtonReleased && has_mouse)
        return true;

    return false;
}

void PartButton::setPosition(const sf::Vector2f &pos)
{

}

sf::Vector2f PartButton::getPosition()
{

}

void PartButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect);
    target.draw(text);
}

void PartButton::release()
{
    pos = sf::Vector2f(0,0);
    text = sf::Text();
}
