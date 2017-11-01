#pragma once
#include "LibsAndDeclarations.h"
#include "configcreator.h"
#include "configparser.h"

class LoadingThingsToMultiStage : public entityx::System<LoadingThingsToMultiStage>
{
	Phisics_2D &phisics;
public:
	LoadingThingsToMultiStage(Phisics_2D &);
	void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);
	~LoadingThingsToMultiStage();
};

