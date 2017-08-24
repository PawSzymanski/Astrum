/*
 *  partsmanager.h
 *
 *  Created: 2017-07-09
 *   Author: Patryk Wojtanowski
 */

#ifndef PARTSMANAGER_H
#define PARTSMANAGER_H

#include "LibsAndDeclarations.h"
#include <vector>
#include <float.h>
#include "configcreator.h"
#include <sstream>
#include "part.h"
#include "keyassigner.h"

class PartsManager : public sf::Drawable
{
	friend class CreatorStage;
    
	sf::VertexArray * current_body;
    std::vector <sf::Vector2f> * current_normals;
    std::string current_body_name;
	std::vector <Part> parts;
	Part * latch_part;
	sf::Transform body_trans;
   
    bool good_place;

    sf::Vector2f mouse_pos;

    KeyAssigner assigner;

private:
    Part * findClicked();

public:
	
    PartsManager();

    void init();
    bool is_body_set();
    void set_body(const std::string &name);
	void loadPartFromFile(std::string dir);
    void add_part(const std::string &name);
    void saveShip(const std::string &dir);
    void input(sf::Event ev);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void release();
};

#endif // PARTSMANAGER_H
