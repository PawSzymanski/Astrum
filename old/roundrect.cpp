/*
 *  roundrect.cpp
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski
 */

#include "roundrect.h"

RoundRect::RoundRect()
    :corner_radius(0), size(sf::Vector2f(0,0))
{

}

RoundRect::RoundRect(const sf::Vector2f &size, float corner_radius)
    :corner_radius(corner_radius), size(size)
{
    update();
}

std::size_t RoundRect::getPointCount() const
{
    return 40;
}

sf::Vector2f RoundRect::getPoint(std::size_t index) const
{
    static const float pi = 3.141592654f;

    bool top_left =index <10;
    bool bottom_right = index>=10 && index <20;
    bool bottom_left = index >=20 && index <30;

    index -= index / 10;

    float angle = (index * ((2 * pi) / 36) - (pi / 2));
    float x = std::cos(angle)* corner_radius;
    float y = std::sin(angle)* corner_radius;

    x = (top_left)? x+size.x : x;
    y = (bottom_left)? y+size.y : y;
    x = (bottom_right)? x+size.x : x;
    y = (bottom_right)? y+size.y : y;

    return sf::Vector2f(x,y);
}
