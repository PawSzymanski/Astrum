/*
 *  part.h
 *
 *  Created: 2017-07-10
 *   Author: Patryk Wojtanowski
 */


#ifndef PART_H
#define PART_H

#include "LibsAndDeclarations.h"

struct Part
{
    Part(){}

    Part(std::string s, sf::VertexArray& v, std::vector< sf::Vector2f >& normals)
        :name(s), v_array(&v), normals(&normals), trans(sf::Transform()), pos(sf::Vector2f(0,0)), key("A"), rot(0.0f) {}

    Part(const Part & other)
        :name(other.name), v_array(other.v_array), texture(other.texture), normals(other.normals),
          trans(other.trans), pos(other.pos), key(other.key), rot(other.rot){}

    Part & operator =(Part && other){
        name = std::move(other.name);
        v_array = std::move(other.v_array);
        normals = std::move(other.normals);
        trans = std::move(other.trans);
        pos = std::move(other.pos);
        rot = std::move(other.rot);
        return *this;
    }

	unsigned int partId;
	float rot;
    std::string name, key;

	std::vector< sf::Vector2f > * normals;
	sf::Vector2f pos;

    sf::VertexArray * v_array;
    sf::Texture * texture;
   
    sf::Transform trans;
};

#endif // PART_H
