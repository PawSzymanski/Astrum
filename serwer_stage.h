#pragma once
#include "LibsAndDeclarations.h"
#include "GameStage.h"

class serwer_stage : public GameStage
{
public:
	serwer_stage();

	virtual bool init() override;
	virtual void input(sf::Event &event) override;
	virtual bool update(float dt) override;
	virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;

	~serwer_stage();
};

