#include "LibsAndDeclarations.h"
#include "ResourceManager.h"
#include "sstream"

void input();
bool update();
void render();

int main()
{
    auto &resource_manager = ResourcesManager::getInstanceRef();

    resource_manager.menu_stage.set();

    while(resource_manager.window.isOpen())
    {
        if(!GameStage::stage_switch())
            resource_manager.exit_stage.set();

        input();

        if(!update())
            resource_manager.window.close();

        render();
    }

    ResourcesManager::deleteInstance();
    return 0;
}

void input()
{
    auto & resource = ResourcesManager::getInstanceRef();
    sf::Event ev;
    while(resource.window.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            resource.exit_stage.set();

        GameStage::stage_input(ev);
    }
}

bool update()
{
    const float dt = 0.01;
    static sf::Clock clock;
    static sf::Time time = sf::Time::Zero;

    time += clock.restart();
    while(time.asSeconds() >= dt)
    {
        if(!GameStage::stage_update(dt))
            return false;

        time -= sf::seconds(dt);
    }

    return true;
}

void render()
{
    static sf::Clock clock;
    auto & resource = ResourcesManager::getInstanceRef();
    sf::Text fps;
    fps.setCharacterSize(6);
    fps.setFillColor(sf::Color::Black);
    fps.setFont(resource.font);
    fps.setPosition(1,1);
    std::stringstream ss;

    ss << ( sf::seconds(1.0f) / clock.restart());

    fps.setString(ss.str());

    resource.window.clear(sf::Color::Cyan);
    GameStage::stage_render(resource.window);
   // resource.window.draw(fps);
    resource.window.display();
}
