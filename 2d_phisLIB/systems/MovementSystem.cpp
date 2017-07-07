#include "MovementSystem.h"



MovementSystem::MovementSystem()
{
}


MovementSystem::~MovementSystem()
{
}

void MovementSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle pos;
	Rotation::Handle rot;
	LinearVelocity::Handle linvel;
	AngularVelocity::Handle angvel;
	Transform::Handle trans;
	std::cout << "ADD BEF disp  " << std::endl;
	for (auto entity : en.entities_with_components(pos, rot, linvel, angvel, trans))
	{
		std::cout << "ADD disp  " << std::endl;
		pos->pos += linvel->vel*static_cast<float>(dt);
		rot->degree += angvel->degree * static_cast<float>(dt);

		sf::Transform transm;
		transm.translate(pos->pos);
		transm.rotate(rot->degree);

		trans->trans = transm;
	}
}
