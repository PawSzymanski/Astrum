#pragma once
#include "LibsAndDeclarations.h"
#include "MenuStage.h"
#include "GameplayStage.h"
#include "ExitStage.h"
#include "lvlsetstage.h"
#include "creatorstage.h"
#include "2d_phisLIB/Container.h"

class ResourcesManager
{
private:
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;
	~ResourcesManager();

private:
	static ResourcesManager *instance;

public:
	static ResourcesManager* getInstance();
	static ResourcesManager& getInstanceRef();
	static void deleteInstance();

public:
    sf::Font font;
	sf::RenderWindow window;
	MenuStage menu_stage;
    LvlSetStage lvl_set_stage;
	GameplayStage gameplay_stage;
    CreatorStage creator_stage;
	ExitStage exit_stage;
	Container vertCont;
	
	entityx::EntityX ex;
	
	Phisics_2D phisics;
	sf::Vector2f gravity;
};
