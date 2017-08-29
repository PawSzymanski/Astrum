/*
 *  destructionsystem.cpp
 *
 *  Created: 2017-07-29
 *   Author: Patryk Wojtanowski
 */

#include "destructionsystem.h"
#include "ResourceManager.h"

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

    if((!en1_is_player && !en2_is_player) || ev.relVel < 100.0f)
        return;

    player = (en1_is_player)? en1 : en2;

    if(player.has_component<AdditionalAnim>())
        return;
	Transform::Handle transH;

	transH = player.component<Transform>();

    auto & resource = ResourcesManager::getInstanceRef();

    boom_anim = player.assign<AdditionalAnim>("explosion",&(resource.textureCont.getTexture("explosion")), resource.vertCont.getPoly("explosion"), 20.0f);
    
	boom_anim->animate = true;
	
    //std::cout << "clock restart " << std::endl;
	
	boom_anim->clock.restart();
	boom_anim->time = sf::Time::Zero;

    //std::cout<<"destruction system receive: "<<ev.relVel<<std::endl;
}