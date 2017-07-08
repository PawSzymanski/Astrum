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

class CreatorStage : public GameStage
{
    PartButton bodybuttons[3];
    PartButton partbuttons[4];
    ButtonMenu start_button;
    sf::Text esc_text;
    sf::RectangleShape mask_rect;

    bool fade_in, fade_out;
    float timer;

    GameStage * next;
    sf::VertexArray * current_body;
    sf::Transform body_transform;

public:
    CreatorStage();

    virtual bool init() override;
    virtual void input(sf::Event &event) override;
    virtual bool update(float dt) override;
    virtual void render(sf::RenderWindow &window) override;
    virtual void release() override;
};

#endif // CREATORSTAGE_H
