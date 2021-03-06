/*
 *  creatorstage.h
 *
 *  Created: 2017-07-07
 *   Author: Patryk Wojtanowski
 */

#ifndef CREATORSTAGE_H
#define CREATORSTAGE_H

#include "LibsAndDeclarations.h"
#include "GameStage.h"
#include "partbutton.h"
#include "ButtonMenu.h"
#include "partsmanager.h"

class CreatorStage : public GameStage
{
	bool fade_in, fade_out;
	bool isHelpSeen, hasHelpMouse;
	float timer;

    PartButton bodybuttons[3];
    PartButton partbuttons[5];
	PartButton garageButtons[4];

    ButtonMenu start_button;
    ButtonMenu save_button;
	sf::Sprite backGroundSprite;
    sf::Text esc_text, helpTextParts, helpTextGarage, help;
	sf::RectangleShape mask_rect;
	

    GameStage * next;

    PartsManager manager;
	void helpUpdate(sf::Event & event);

public:
    CreatorStage();

    virtual bool init() override;
    virtual void input(sf::Event &event) override;
    virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
    virtual void release() override;
};

#endif // CREATORSTAGE_H
