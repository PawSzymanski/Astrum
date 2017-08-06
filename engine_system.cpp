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
	
	AttachToPlayerPoint::Handle attachPointH;
	Transform::Handle transEngH, transPlayerH;
	isLegs::Handle legsH;

	for (auto en1 : en.entities_with_components(posH, playerH, rotH))
	{
		for (auto en2 : en.entities_with_components(verH, transEngH, attachPointH))
		{

			rotH = en1.component<Rotation>();
			posH = en1.component<Position>();

			verH = en2.component<VertexArray>();
			transEngH = en2.component<Transform>();
			rotEngH = en2.component<Rotation>();
			attachPointH = en2.component<AttachToPlayerPoint>();
			rotEngH = en2.component<Rotation>();

			transEngH->trans = transEngH->defaultTrans;

			//std::cout << posH->pos.x << "  " << posH->pos.y << std::endl;

			sf::Transform rotMatrix;
			rotMatrix.rotate(rotH->degree);

			attachPointH->point = rotMatrix * attachPointH->point;

			transEngH->trans.translate(posH->pos + attachPointH->point);
			transEngH->trans.rotate(rotH->degree + rotEngH->degree);
			//update

			//parts functions///////////////////////////////////////////////////////////////////////////
			
			enginePart(en1, en2, ev, attachPointH, rotMatrix);

			//end;/////////////////////////////////////////////////////////////////////////////////////////
			attachPointH->point = rotMatrix.getInverse() * attachPointH->point;
		}
	}
}

void engine_system::enginePart(entityx::Entity enPlayer, entityx::Entity enPart, entityx::EventManager & ev, AttachToPlayerPoint::Handle attachPointH, sf::Transform rotMatrix)
{
	if (!enPart.has_component<isEngine>())
	{
		return;
	}
	KeyAssigned::Handle keyH;
	ForcePoint::Handle pointH;
	pointH = enPart.component<ForcePoint>();
	keyH = enPart.component<KeyAssigned>();

	pointH->force = rotMatrix * pointH->force;

	if (sf::Keyboard::isKeyPressed(keyH->key))
	{
		ev.emit<ApplyForceEvent>(attachPointH->point, pointH->force, enPlayer);
	}
	pointH->force = rotMatrix.getInverse() * pointH->force;
}

void engine_system::receive(const ApplyForceEvent & ev)
{
	LinearVelocity::Handle velH;
	entityx::Entity en = ev.en;
	velH = en.component<LinearVelocity>();
}


engine_system::~engine_system()
{
}
