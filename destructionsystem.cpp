#include "destructionsystem.h"

DestructionSystem::DestructionSystem(entityx::EntityX &ex)
{
    ex.events.subscribe<CollisionEvent>(*this);
}

void DestructionSystem::update(entityx::EntityManager &en, entityx::EventManager &ev, double dt)
{

}

void DestructionSystem::receive(const CollisionEvent &ev)
{
    auto en1 = ev.en1;
    auto en2 = ev.en2;
    bool en1_is_player = en1.has_component<isPlayer>(),
         en2_is_player = en2.has_component<isPlayer>();

    if(!en1_is_player && !en2_is_player)
        return;

    entityx::Entity player = (en1_is_player)? en1 : en2;
    entityx::Entity obstacle = (en1_is_player)? en2 : en1;



    std::cout<<"destruction system receive: "<<ev.relVel<<std::endl;
}
