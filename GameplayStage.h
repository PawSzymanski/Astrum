#pragma once

#include "LibsAndDeclarations.h"
#include "GameStage.h"

class GameplayStage : public GameStage
{
public:
	GameplayStage();
	GameplayStage(const GameplayStage&) = delete;
	GameplayStage& operator=(const GameplayStage&) = delete;
	virtual ~GameplayStage();

private:
	sf::View camera;

	void updateCamera();

public:
	virtual bool init() override;
	virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;
    virtual void input(sf::Event &event) override;
};
