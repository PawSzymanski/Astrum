#pragma once

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

struct ApplyForceEvent
{
	ApplyForceEvent(sf::Vector2f point, sf::Vector2f force, entityx::Entity en)
		:point(point), force(force), en(en) {}
	ApplyForceEvent(sf::Vector2f point, sf::Vector2f force, sf::Vector2f posAftCorr,entityx::Entity en)
		:point(point), force(force), en(en), posAftCorr(posAftCorr) {}
	sf::Vector2f point, force, posAftCorr;
	entityx::Entity en;
	sf::Vector2f correction;
};

struct CollisionEvent
{
    CollisionEvent(entityx::Entity en1, entityx::Entity en2, float relVel, sf::Vector2f contact)
        :en1(en1), en2(en2), relVel(relVel), contact(contact){}
    entityx::Entity en1, en2;
    float relVel;
    sf::Vector2f contact;
};
