#include "lvlsetstage.h"
#include "ResourceManager.h"

LvlSetStage::LvlSetStage()
{

}

LvlSetStage::~LvlSetStage()
{

}

bool LvlSetStage::init()
{
    next_stage = nullptr;

    auto & resource = ResourcesManager::getInstanceRef();

    button[0].init(sf::Vector2f(-550,600/2), 1, "sample text 1", resource.font);
    button[1].init(sf::Vector2f(-350,600/2), 2, "sample text 2", resource.font);
    button[2].init(sf::Vector2f(-150,600/2), 3, "sample text 3", resource.font);

    slide_in = true;
    slide_out = false;

    esc_text.setCharacterSize(32);
    esc_text.setFillColor(sf::Color::White);
    esc_text.setPosition(50,50);
    esc_text.setFont(resource.font);
    esc_text.setString("Menu:  ESC");

    return true;
}

void LvlSetStage::input(sf::Event &event)
{
    static int high_nr = 0;

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            next_stage = &(ResourcesManager::getInstanceRef().menu_stage);
            slide_out = true;
        }
        else if( event.key.code == sf::Keyboard::Left)
        {
            std::cout<<"left"<<std::endl;
            high_nr--;

        }
        else if( event.key.code == sf::Keyboard::Right)
        {
            std::cout<<"right"<<std::endl;
            high_nr++;
        }
    }
    high_nr= (high_nr<0)? 2:high_nr;
    high_nr= (high_nr>2)? 0:high_nr;

    for(int i=0; i<3; ++i)
    {
        button[i].highlighted = (i==high_nr);
    }

    for(int i=0; i<3; ++i)
        if(button[i].input(event))
        {
            slide_out = true;
            next_stage = &(ResourcesManager::getInstanceRef().gameplay_stage);
        }
}

bool LvlSetStage::update(float dt)
{
    if(slide_in)
    {
        float pos_x[3] = {450,650,850};
            bool in_pos = true;
        for(int i=0; i<3; ++i)
        {
            sf::Vector2f pos = button[i].getPosition();
            float dp = pos.x - pos_x[i] ;
            if(dp < -40)
            {
                button[i].setPosition(pos + sf::Vector2f(-dp/50,0));
                in_pos = false;
            }
        }

        slide_in = !in_pos;
    }
    if(slide_out)
    {
       float pos_x[3] = {1450,1650,1850};
        bool in_pos = true;
        for(int i=0; i<3; ++i)
        {
            sf::Vector2f pos = button[i].getPosition();
            float dp = pos.x - pos_x[i] ;
            if(dp < -40)
            {
                button[i].setPosition(pos + sf::Vector2f(-dp/50,0));
                in_pos = false;
            }
        }

        slide_out = !in_pos;
    }

    if(next_stage && !slide_out)
        next_stage->set();

    return true;
}

void LvlSetStage::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    for(int i=0; i<3; ++i)
        window.draw(button[i]);
    window.draw(esc_text);
}

void LvlSetStage::release()
{
    esc_text = sf::Text();
    next_stage = nullptr;
    for(int i=0; i<3; ++i)
        button[i].release();
}
