#pragma once
#include "LibsAndDeclarations.h"
#include "MenuStage.h"
#include "GameplayStage.h"
#include "ExitStage.h"
#include "lvlsetstage.h"
#include "creatorstage.h"
#include "creatorstageMulti.h"
#include "login_stage.h"
#include "serwer_stage.h"
#include "multiplayer_stage.h"
#include "2d_phisLIB/Container.h"
#include "configparser.h"
/*
*We keep here data that can be transefed 
* or visible to any class or function in whole code.
*
*
*/
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

	bool isMovingCameraOn;
	//game_over_system resources
	bool areAllPlatfIncluded, areAllCargoSpaceIncluded, isMouseButtonReleased, isGameOver, isPauseTime;
	sf::Text winText;
	ButtonMenu GOButton[4];
	std::shared_ptr<sf::Event> mainEvent;


	sf::View camera;
	std::string levelInfo;
	std::string shipInfo, shipInfoMulti;
	std::string decodeOneLineDel(std::string & array);
	std::string decodeOneLineRead(std::string  array);

	Container vertCont;
	Container textureCont;
    sf::Font font;
	sf::RenderWindow window;
	
	//Offline sages
	MenuStage menu_stage;
    LvlSetStage lvl_set_stage;
	GameplayStage gameplay_stage;
    CreatorStage creator_stage;
	ExitStage exit_stage;

////////////////////////////////////////////////////////////////////////////////////////////
	//Multiplayer zone:
	login_stage login_stage;
	CreatorStageMulti creator_stage_multi;
	multiplayer_stage multi_stage;
	serwer_stage serwer_stage;
	
	unsigned short portRec;
	std::string buffer, ip;
};
