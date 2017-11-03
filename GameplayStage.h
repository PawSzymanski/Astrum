#pragma once

#include "LibsAndDeclarations.h"
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

#define CAMERA_CONST_X 3
#define CAMERA_CONST_Y 1.5

class GameplayStage : public GameStage
{
public:
	GameplayStage(Container &);
	GameplayStage(const GameplayStage&) = delete;
	GameplayStage& operator=(const GameplayStage&) = delete;
	virtual ~GameplayStage();

private:
	float cameraX, cameraY, dtime;

	sf::Vector2f gravity;
	sf::Time display_fps_time;
	std::unique_ptr<entityx::EntityX> ex_ptr;
	std::unique_ptr<Phisics_2D> phisics_ptr;

	Container &vertCont;

    sf::Text fps_text;
public:

	virtual bool init() override;
	virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;
    virtual void input(sf::Event &event) override;

private:

	void updateCamera();
};
