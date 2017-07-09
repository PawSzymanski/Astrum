#ifndef PARTSMANAGER_H
#define PARTSMANAGER_H

#include "LibsAndDeclarations.h"
#include <vector>
#include <float.h>

struct Part
{
    Part(std::string s, sf::VertexArray& v)
        :name(s), v_array(v), trans(sf::Transform()){}
    std::string name;
    sf::VertexArray& v_array;
    sf::Transform trans;
};

class PartsManager : public sf::Drawable
{
    sf::VertexArray * current_body;
    std::vector <sf::Vector2f> * current_normals;
    std::string current_body_name;

    Part * latch_part;
    float latch_part_rot;
    sf::Vector2f latch_part_pos;
    std::vector <Part> parts;
    sf::Transform body_trans;

public:
    PartsManager();

    void init();
    void set_body(const std::string &name);
    void add_part(const std::string &name);
    void input(sf::Event ev);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void release();
};

#endif // PARTSMANAGER_H
