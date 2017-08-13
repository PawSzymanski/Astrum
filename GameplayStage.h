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

class GameplayStage : public GameStage
{
public:
	GameplayStage(Container &);
	GameplayStage(const GameplayStage&) = delete;
	GameplayStage& operator=(const GameplayStage&) = delete;
	virtual ~GameplayStage();

private:
	
	sf::Time display_fps_time;
	sf::View camera;
	float dtime;
	void updateCamera();
	sf::Vector2f gravity;
	Container &vertCont;
	std::unique_ptr<entityx::EntityX> ex_ptr;
	std::unique_ptr<Phisics_2D> phisics_ptr;

    sf::Text fps_text;
public:

	virtual bool init() override;
	virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;
    virtual void input(sf::Event &event) override;
};
