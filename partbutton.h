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
	float rot;

    std::string part_name;

	sf::VertexArray * v_array;
	sf::Texture *texture;
public:
    PartButton();

	bool input(sf::Event & ev);

    void init(sf::Vector2f pos, std::string text, sf::Font & font, std::string name);
    void update(float dt);
    void setPosition(const sf::Vector2f& pos);
	void release();
    
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f getPosition() const;
   
	const std::string & getName() const;
};

#endif // PARTBUTTON_H
