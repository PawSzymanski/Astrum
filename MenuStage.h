#pragma once

#include "LibsAndDeclarations.h"
#include "GameStage.h"

class MenuStage : public GameStage
{
public:
	MenuStage();
	MenuStage(const MenuStage&) = delete;
	MenuStage& operator=(const MenuStage&) = delete;
	virtual ~MenuStage();

private:
	
	uint8_t actionCode;
	sf::Font font;
	sf::Text start_message, options_message, exit_message;

public:
	virtual bool init() override;
	virtual bool update(float dt) override;
	virtual void draw(sf::RenderWindow &window) override;
	virtual void release() override;
	virtual void eventsManage(sf::Event &event) override;
private:
	void returnFun();
	void showBar();
};
