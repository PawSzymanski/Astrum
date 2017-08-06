#include "cranesystem.h"

CraneSystem::CraneSystem(entityx::EntityX &ex)
{
    ex.events.subscribe<CollisionEvent>(*this);
}

void CraneSystem::update(entityx::EntityManager &en, entityx::EventManager &ev, double dt)
{
    isCrane::Handle crane;
    KeyAssigned::Handle key;

    for(auto en : en.entities_with_components(crane, key))
    {
        if(sf::Keyboard::isKeyPressed(key->key))
        {
            if(!crane->block)
            {
                std::cout<<"crane switch"<<std::endl;
                crane->block = true;

            }
        }
        else
            crane->block = false;
    }
}

void CraneSystem::receive(const CollisionEvent &ev)
{

}
