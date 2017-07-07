/*
 *  lvlbutton.cpp
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski
 */

#include "lvlbutton.h"

LvlButton::LvlButton()
{
}

void LvlButton::init(sf::Vector2f pos, int num, std::string text, sf::Font &font)
{

    highlighted = false;
    this->pos = pos;
    rect.corner_radius = 10;
    rect.size = sf::Vector2f(100,100);
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(10);
    rect.setPosition(pos);

    std::stringstream ss;
    ss<<num;
    this->num.setPosition(pos + sf::Vector2f(30,-30));
    this->num.setFillColor(sf::Color::White);
    this->num.setCharacterSize(128);
    this->num.setFont(font);
    this->num.setString(ss.str());

    this->text.setPosition(pos + sf::Vector2f(-20,120));
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(28);
    this->text.setFont(font);
    this->text.setString(text);
}

bool LvlButton::input(sf::Event &ev)
{
    rect.setOutlineThickness((has_mouse || highlighted)? 15 : 10);

    if(ev.type == sf::Event::MouseMoved)
    {
        has_mouse = (ev.mouseMove.x > pos.x && ev.mouseMove.x < pos.x + rect.size.x &&
                ev.mouseMove.y > pos.y && ev.mouseMove.y < pos.y + + rect.size.y);
    }
    else if(ev.type == sf::Event::MouseButtonReleased && has_mouse)
        return true;
    else if(highlighted && ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return)
    {
        std::cout<<"return"<<std::endl;
        return true;

    }

    return false;
}

void LvlButton::setPosition(const sf::Vector2f &pos)
{
    this->pos = pos;
    rect.setPosition(pos);
    num.setPosition(pos + sf::Vector2f(30,-30));
    text.setPosition(pos + sf::Vector2f(-20,120));
}

sf::Vector2f LvlButton::getPosition()
{
    return pos;
}

void LvlButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect);
    target.draw(num);
    target.draw(text);
}

void LvlButton::release()
{
    highlighted = false;
    pos = sf::Vector2f(0,0);
    num = sf::Text();
    text = sf::Text();
}
