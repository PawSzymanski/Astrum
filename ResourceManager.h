#pragma once
#include "LibsAndDeclarations.h"
#include "MenuStage.h"
#include "GameplayStage.h"
#include "ExitStage.h"
#include "lvlsetstage.h"
#include "creatorstage.h"
#include "2d_phisLIB/Container.h"
#include "configparser.h"

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

private:
    void loadContainer();

public:
	static ResourcesManager* getInstance();
	static ResourcesManager& getInstanceRef();
	static void deleteInstance();

public:
	std::string levelInfo;
	std::string shipInfo;
	Container vertCont;
    sf::Font font;
	sf::RenderWindow window;
	MenuStage menu_stage;
    LvlSetStage lvl_set_stage;
	GameplayStage gameplay_stage;
    CreatorStage creator_stage;
	ExitStage exit_stage;

	
	
	
	
};
