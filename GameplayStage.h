#pragma once

#include "LibsAndDeclarations.h"
#include "GameStage.h"
#include "engine_system.h"
#include "player_input_system.h"
#include "render_system.h"


class GameplayStage : public GameStage
{
public:
	GameplayStage(Container &);
	GameplayStage(const GameplayStage&) = delete;
	GameplayStage& operator=(const GameplayStage&) = delete;
	virtual ~GameplayStage();

private:
	sf::View camera;
	float dtime;
	void updateCamera();
	sf::Vector2f gravity;
	//Phisics_2D phisics;
	Container &vertCont;
	std::unique_ptr<entityx::EntityX> ex_ptr;
	std::unique_ptr<Phisics_2D> phisics_ptr;
	//entityx::EntityX ex;
public:

	virtual bool init() override;
	virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;
    virtual void input(sf::Event &event) override;
};
