#pragma once
#include "LibsAndDeclarations.h"

#include "LoadingThingsToMultiStage.h"

#include "GameStage.h"
#include "engine_system.h"
#include "player_input_system.h"
#include "render_system.h"
#include "destructionsystem.h"
#include "cranesystem.h"
#include "platform_manager.h"
#include "animations_system.h"
#include "cargosystem.h"
#include "game_over_system.h"
#include "enemy_system.h"
#include "sliding_doors_system.h"




class multiplayer_stage : public GameStage
{
	/////////////////////////////
	struct PlayersInfo
	{
		unsigned int iD;
		float rot;
		sf::Vector2f pos;
		entityx::Entity entity;
		std::string bodyname;
	};
	//////////////////////////////
	std::unique_ptr<entityx::EntityX> ex_ptr;
	std::unique_ptr<Phisics_2D> phisics_ptr;
	
	unsigned int thisPlayerId;

	sf::Time inputSendTime;
	sf::Clock inputSendClock;
	sf::Clock clock;
	sf::Time time;
	
	std::vector<PlayersInfo> players;
	
	sf::UdpSocket socket;
public:
	multiplayer_stage();

	bool sendMessage();
	bool reciveMessage();
	bool addPlayer();
	bool setPositonOfPlayer();

	virtual bool init() override;
	virtual void input(sf::Event &event) override;
	virtual bool update(float dt) override;
	virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;

	void updatePartsActions();

	~multiplayer_stage();
};

