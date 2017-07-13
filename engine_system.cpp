#include "engine_system.h"



engine_system::engine_system(entityx::EventManager &ev)
{
	ev.subscribe<ApplyForceEvent>(*this);
}

void engine_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	isPlayer::Handle playerH;
	VertexArray::Handle verH;
	//Line::Handle lineH;
	Rotation::Handle rotH, rotEngH;
	Position::Handle posH, posPlayerH;
	ForcePoint::Handle pointH;
	KeyAssigned::Handle keyH;
	LinearVelocity::Handle velH;
	Transform::Handle transEngH, transPlayerH;
	isLegs::Handle legsH;

	for (auto en1 : en.entities_with_components(posH, playerH, transPlayerH, rotH))
	{
		for (auto en2 : en.entities_with_components(verH, pointH, keyH, velH, transEngH ))
		{
			rotH = en1.component<Rotation>();
			posH = en1.component<Position>();
			transPlayerH = en1.component<Transform>();

			pointH = en2.component<ForcePoint>();
			keyH = en2.component<KeyAssigned>();
			verH = en2.component<VertexArray>();
			transEngH = en2.component<Transform>();
			rotEngH = en2.component<Rotation>();
	
			transEngH->trans = transEngH->defaultTrans;

			//rotating force
			sf::Transform rotMatrix;
			rotMatrix.rotate(rotH->degree);

			pointH->point = rotMatrix * pointH->point;
			pointH->force = rotMatrix * pointH->force;
			
			std::cout << posH->pos.x << "  " << posH->pos.y << std::endl;

			transEngH->trans.translate(posH->pos + pointH->point);
			transEngH->trans.rotate(rotH->degree + rotEngH->degree);

			if (sf::Keyboard::isKeyPressed(keyH->key))
			{			
				ev.emit<ApplyForceEvent>(pointH->point, pointH->force, en1);
			}
			pointH->point = rotMatrix.getInverse() * pointH->point;
			pointH->force = rotMatrix.getInverse() * pointH->force;	
		}
	}
}

void engine_system::receive(const ApplyForceEvent & ev)
{
	LinearVelocity::Handle velH;
	entityx::Entity en = ev.en;
	velH = en.component<LinearVelocity>();
	//std::cout << " lenghhhhhh: " << vecLenght(velH->vel) << std::endl;
	
	//if (vecLenght(velH->vel) > 0.5)
	//	std::cout << " lenghhhhhh: " << vecLenght(velH->vel) << std::endl;
	//if (vecLenght(vecLenght))
}


engine_system::~engine_system()
{
}
