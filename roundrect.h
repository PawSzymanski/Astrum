/*
 *  roundrect.h
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski
 */

#ifndef ROUNDRECT_H
#define ROUNDRECT_H

#include "LibsAndDeclarations.h"

class RoundRect: public sf::Shape
{
public:
    RoundRect();
    RoundRect(const sf::Vector2f& size, float corner_radius);

    float corner_radius;
    sf::Vector2f size;

    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;
};

#endif // ROUNDRECT_H
