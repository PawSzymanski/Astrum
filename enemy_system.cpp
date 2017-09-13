#include "enemy_system.h"
#include "ResourceManager.h"


enemy_system::enemy_system(Phisics_2D &phs) : phisics(phs), detectionSpace(sf::Vector2f(0, 0.1)), dir(true)
{
}


void enemy_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle posCamH, posPlaH;
	isEnemyCam::Handle camH;
	isPlayer::Handle playerH;
	Rotation::Handle rotCamH;
	

	//shooting camera
	for (auto ent : en.entities_with_components<>(camH, posCamH))
	{
		entityx::Entity newEnt;
		for (auto e : en.entities_with_components<>(playerH))
		{
			newEnt = e;
		}
		posPlaH = newEnt.component<Position>();
		rotCamH = ent.component<Rotation>();
	
		
		if (vecLenghtSq(detectionSpace) < 16 && dir)
		{
			detectionSpace -= sf::Vector2f(0 ,0.1);
			
		}
		else
		{
			dir = false;
			if ((vecLenghtSq(detectionSpace) < 0.25))
				dir = true;
			
			detectionSpace += sf::Vector2f(0 , 0.1);
		}
		sf::Transform trans ;
		trans.rotate(rotCamH->degree);
		detectionSpace = trans * detectionSpace;
		detectionSpace += posCamH->pos;

		std::cout << rotCamH->degree << " det: " << detectionSpace.x << " " << detectionSpace.y << std::endl;

		if (bulletTime.asMilliseconds() > 180 &&
			posPlaH->pos.x > detectionSpace.x - 0.5 &&
			posPlaH->pos.x < detectionSpace.x + 0.5 &&
			posPlaH->pos.y > detectionSpace.y - 0.5 &&
			posPlaH->pos.y < detectionSpace.y + 0.5 )
		{
			std::cout << "shooooot \n";
			auto bulletEn = en.create();
			bulletTime = sf::Time::Zero;

			phisics.createPolygon(bulletEn, posCamH->pos,
				trans * sf::Vector2f(0, -8), 0, 1, "bullet");
			bulletEn.assign<isBullet>(true);
		}
		bulletTime += bulletClock.restart();

		//end, don't edit
		detectionSpace -= posCamH->pos;
		detectionSpace = trans.getInverse() * detectionSpace;
	}
}


enemy_system::~enemy_system()
{
}
