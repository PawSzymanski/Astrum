#pragma once

#include <random>

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
	
	bool isPressed;
	int actionCode, isSliding;
	float xAnimMove, yAnimMove, animRot;
	float buttonSpeed;
	sf::Font font;
	ButtonMenu startButton,
		optionsButton,
		exitButton,
		multiButton;
	sf::Vector2u windowSize;
	sf::Texture shipTexture[3];
	sf::Sprite backGroundSprite;

	struct aniamtion {
		aniamtion(sf::Sprite s) : spr(s){}

		float x, y, rot;
		sf::Sprite spr;
	};

	std::vector<aniamtion> animVec;

public:
	void animationsUpdate();
	virtual bool init() override;
	virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;
    virtual void input(sf::Event &event) override;

private:
	void showBar();
	void slidingRight(float dt);
	void slidingLeft(float dt);
};
