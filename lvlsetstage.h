/*
 *  lvlsetstage.h
 *
 *  Created: 2017-07-06
 *   Author: Patryk Wojtanowski
 */

#ifndef LVLSETSTAGE_H
#define LVLSETSTAGE_H

#include "LibsAndDeclarations.h"
#include "GameStage.h"
#include "lvlbutton.h"

class LvlSetStage :public GameStage
{
	bool slide_in, slide_out, slide_out_to_menu, wasLastXMouse;

	int numberOfLevels;
	int lastXMouse;

	float timer, speed;

	std::string ships[3];
	std::string levels[5];

	LvlButton button[5];
    GameStage * next_stage;
    sf::Text esc_text;
    
public:
    LvlSetStage();
    LvlSetStage(const LvlSetStage&) = delete;
    LvlSetStage& operator=(const LvlSetStage&) = delete;
    ~LvlSetStage();

    virtual bool init() override;
    virtual void input(sf::Event &event) override;
    virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
    virtual void release() override;

};

#endif // LVLSETSTAGE_H
