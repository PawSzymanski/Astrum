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
    sf::VertexArray * v_array;
    sf::Texture *texture;
    float rot;

    std::string part_name;

public:
    PartButton();

    void init(sf::Vector2f pos, std::string text, sf::Font & font, std::string name);
    bool input(sf::Event & ev);
    void update(float dt);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    const std::string & getName() const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void release();
};

#endif // PARTBUTTON_H
