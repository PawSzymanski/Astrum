/*
 *  partbutton.cpp
 *
 *  Created: 2017-07-07
 *   Author: Patryk Wojtanowski
 */

#include "partbutton.h"
#include "ResourceManager.h"

PartButton::PartButton()
    :v_array(nullptr)
{

}

void PartButton::init(sf::Vector2f pos, std::string text, sf::Font &font, std::string name)
{
    part_name = name;
    rot = 0;
    this->pos = pos;
    rect.corner_radius = 6;
    rect.size = sf::Vector2f(60,60);
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(6);
    rect.setPosition(pos);

    this->text.setPosition(pos + sf::Vector2f(-10,70));
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(18);
    this->text.setFont(font);
    this->text.setString(text);

    auto & resource = ResourcesManager::getInstanceRef();
    v_array = &(resource.vertCont.getPoly(name));

    if(part_name == "small_engine" || part_name == "large_engine")
        texture = &(ResourcesManager::getInstanceRef().textureCont.getTexture("small_engine"));
    else
        texture = nullptr;

    assert(v_array);
}

bool PartButton::input(sf::Event &ev)
{
    rect.setOutlineThickness((has_mouse)? 10 : 6);

    if(ev.type == sf::Event::MouseMoved)
    {
        has_mouse = (ev.mouseMove.x > pos.x && ev.mouseMove.x < pos.x + rect.size.x &&
                ev.mouseMove.y > pos.y && ev.mouseMove.y < pos.y + + rect.size.y);
    }
    else if(ev.type == sf::Event::MouseButtonReleased && has_mouse)
        return true;

    return false;
}

void PartButton::update(float dt)
{
    rot += 50*dt;
}

void PartButton::setPosition(const sf::Vector2f &pos)
{

}

sf::Vector2f PartButton::getPosition() const
{

}

const std::string &PartButton::getName() const
{
    return part_name;
}

void PartButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Transform trans;
    trans.translate(pos+ sf::Vector2f(30,30));
    trans.scale(30,30);
    trans.rotate(rot);

    if(v_array == nullptr)
    {
        assert(false);
    }

    //std::cout<<(*v_array)[0].position.x<<std::endl;
    sf::RenderStates united_states;

    //v_array[0][0].texCoords = sf::Vector2f(0, 0);
    //v_array[0][1].texCoords = sf::Vector2f(31, 0);
    //v_array[0][2].texCoords = sf::Vector2f(31, 24);
    //v_array[0][3].texCoords = sf::Vector2f(0, 24);

    united_states.texture = texture;
    united_states.transform = trans;
    target.draw(*v_array, united_states);

    target.draw(rect);
    target.draw(text);
}

void PartButton::release()
{
    pos = sf::Vector2f(0,0);
    text = sf::Text();
    rot = 0;
    part_name = std::string();
}
