/*
 *  keyassigner.h
 *
 *  Created: 2017-07-10
 *   Author: Patryk Wojtanowski
 */

#ifndef KEYASSIGNER_H
#define KEYASSIGNER_H

#include "LibsAndDeclarations.h"
#include "part.h"

class KeyAssigner : public sf::Drawable
{
    Part * part;
public:
    KeyAssigner();
    void assign(Part * p);
    void input(sf::Event& ev);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void release();

};

#endif // KEYASSIGNER_H
