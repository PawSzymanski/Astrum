/*
 *  creatorstage.h
 *
 *  Created: 2017-07-07
 *   Author: Patryk Wojtanowski
 */

#pragma once

#include "LibsAndDeclarations.h"
#include "GameStage.h"
#include "partbutton.h"
#include "ButtonMenu.h"
#include "partsmanagerMulti.h"

class CreatorStageMulti : public GameStage
{
    PartButton bodybuttons[3];
    PartButton partbuttons[5];
	PartButton garageButtons[4];

    ButtonMenu start_button;
    ButtonMenu save_button;

    sf::Text esc_text;
    sf::RectangleShape mask_rect;

    bool fade_in, fade_out;
    float timer;

    GameStage * next;

    PartsManagerMulti manager;

public:
    CreatorStageMulti();

	bool sendMessageToSerwer();

	bool reciveMessageFromSerwer();

    virtual bool init() override;
    virtual void input(sf::Event &event) override;
    virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
    virtual void release() override;
};


