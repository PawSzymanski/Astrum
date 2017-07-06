#ifndef LVLSETSTAGE_H
#define LVLSETSTAGE_H

#include "LibsAndDeclarations.h"
#include "GameStage.h"

class LvlSetStage :public GameStage
{
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
