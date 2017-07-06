#pragma once

#include "LibsAndDeclarations.h"
#include "GameStage.h"
#include "ButtonMenu.h"

class MenuStage : public GameStage
{
public:
	MenuStage();
	MenuStage(const MenuStage&) = delete;
	MenuStage& operator=(const MenuStage&) = delete;
	virtual ~MenuStage();

private:
	
	bool isPressed, isSliding;
	uint8_t actionCode;
	float buttonSpeed;
	sf::Font font;
	ButtonMenu startButton,
		optionsButton,
		exitButton;
	sf::Vector2u windowSize;



public:
	virtual bool init() override;
	virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;
    virtual void input(sf::Event &event) override;

private:
	void showBar();
	void slidingRight(float dt);
};
