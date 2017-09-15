#include "sliding_doors_system.h"



sliding_doors_system::sliding_doors_system() : dist(0)
{
}

void sliding_doors_system::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	isSlidingDoors::Handle doorsH;

	//checking conditions to open doors;
	for (auto e : en.entities_with_components<>(doorsH))
	{
		if (!doorsH->isOpen)
		{
			for (int i = 0; i < doorsH->opener.size(); ++i)
			{
				//you can add more things taht can be passed (one if one thing)
				if (doorsH->opener[i] == "platform")
				{
					isPlatform::Handle platH;
					for (auto plat : en.entities_with_components<>(platH))
					{
						if (doorsH->id[i] == platH->id)
						{
							if (!platH->isPassed)
							{
								doorsH->isOpen = false;
								return;
							}
							else
							{
								doorsH->isOpen = true;
							}
						}
					}
				}
				else if (doorsH->opener[i] == "cargo_space")
				{
					CargoSpace::Handle cargoH;
					for (auto cargo : en.entities_with_components<>(cargoH))
					{
						if (doorsH->id[i] == cargoH->id)
						{
							if (!cargoH->checked)
							{
								doorsH->isOpen = false;
								return;
							}
							else
							{
								doorsH->isOpen = true;
							}
						}
					}
				}

			}
		}
		//if good open
		else
		{
			openDoors(e);
		}
	}
}

void sliding_doors_system::openDoors(entityx::Entity ent)
{
	Position::Handle posH = ent.component<Position>();
	Rotation::Handle rotH = ent.component<Rotation>();
	if (dist < 2.5)
	{
		sf::Transform trans;
		trans.rotate(rotH->degree);

		posH->pos += trans * sf::Vector2f(0.1, 0);
		this->dist += 0.1;
	}
}


sliding_doors_system::~sliding_doors_system()
{
}
