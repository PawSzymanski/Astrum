#include "partsmanager.h"
#include "ResourceManager.h"

PartsManager::PartsManager()
{

}

void PartsManager::init()
{
    current_body = nullptr;
    current_normals = nullptr;
    latch_part = nullptr;
    latch_part_rot = 0;
    latch_part_pos = sf::Vector2f(0,0);

    body_trans.translate(650, 500);
    body_trans.scale(200,200);
}

void PartsManager::set_body(const std::string &name)
{
    if(parts.size() > 0)
        return;

    current_body_name = name;
    current_body = &(ResourcesManager::getInstanceRef().vertCont.getPoly(name));
    current_normals = &(ResourcesManager::getInstanceRef().vertCont.getNormals(name));
}

void PartsManager::add_part(const std::string &name)
{
    if(latch_part)
        return;

    sf::VertexArray &temp = ResourcesManager::getInstanceRef().vertCont.getPoly(name);
    parts.push_back(Part(name, temp));
    latch_part =  &(parts.at( parts.size() -1 ));
}

void PartsManager::input(sf::Event ev)
{
    if(ev.type == sf::Event::MouseMoved && latch_part)
    {
        latch_part_pos = sf::Vector2f(ev.mouseMove.x, ev.mouseMove.y);
        latch_part->trans = sf::Transform();
        latch_part->trans.translate(latch_part_pos);
        latch_part->trans.scale(200, 200);
        latch_part->trans.rotate(latch_part_rot);
    }
    else if(ev.type == sf::Event::MouseWheelScrolled && latch_part)
    {
        latch_part_rot += ev.mouseWheelScroll.delta * 10;
        latch_part->trans.rotate(ev.mouseWheelScroll.delta * 10);
    }
    else if( ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Delete && latch_part)
    {
        latch_part = nullptr;
        latch_part_rot = 0;
        parts.pop_back();
    }

    if(!current_body || !latch_part)
        return;

    unsigned int size = current_body->getVertexCount();
    sf::Vector2f pos = body_trans.getInverse() * latch_part_pos;

    sf::Vector2f best_normal;
    float best_distance = FLT_MAX;

    for(int i=0 ; i <size; ++i)
    {
        sf::Vector2f normal =  current_normals->at(i);
        sf::Vector2f vert_to_point = pos - (*current_body)[i].position;
        float dist = dot(normal,vert_to_point);
        bool good = abs_f(dist) < best_distance;
        best_distance = (good)? dist: best_distance;
        best_normal = (good)? normal : best_normal;
    }

    std::cout<<"best distance: "<<best_distance<<std::endl;
}

void PartsManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(current_body)
        target.draw(*current_body, body_trans);

    for(auto &p: parts)
    {
        target.draw(p.v_array, p.trans);
    }
}

void PartsManager::release()
{
    current_body = nullptr;
    current_normals = nullptr;
    latch_part = nullptr;

    current_body_name = std::string();
    parts.clear();
}
