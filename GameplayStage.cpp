#include "GameplayStage.h"
#include "ResourceManager.h"

GameplayStage::GameplayStage(Container &cont) : gravity(0.0f, 9.8), vertCont(cont)
{

}

GameplayStage::~GameplayStage()
{
	release();
}

void GameplayStage::updateCamera()
{
	//camera.reset(sf::FloatRect(0, 0, 17.5, 10));
}

bool GameplayStage::init()
{
	ex_ptr = std::make_unique<entityx::EntityX>();
	phisics_ptr = std::make_unique<Phisics_2D>((*ex_ptr), vertCont, gravity);
	(*phisics_ptr).init();


	auto &window = ResourcesManager::getInstanceRef().window;
	camera.reset(sf::FloatRect(0, 0, 17.5, 10));


	(*ex_ptr).systems.add<engine_system>();
	(*ex_ptr).systems.add<player_input_system>(*phisics_ptr);
	(*ex_ptr).systems.add<render_system>(window);


	(*ex_ptr).systems.update<player_input_system>(dtime);

    fps_text.setCharacterSize(18);
    fps_text.setFillColor(sf::Color::Black);
    fps_text.setFont(ResourcesManager::getInstanceRef().font);
    fps_text.setPosition(sf::Vector2f(60,20));
    fps_text.setString("NULL");


    return true;
}

bool GameplayStage::update(float dt)
{
	dtime = dt;
	
	updateCamera();

	//if (ecs_gameplay_ptr->update(dt)) return true;

	
	(*ex_ptr).systems.update<engine_system>(dt);
	(*phisics_ptr).update(dt);
	
    //render

	
	return true;
}

void GameplayStage::render(sf::RenderWindow &window)
{
    static sf::Clock fps_clock;
    std::stringstream ss;
    float fps_f = (1.0f/fps_clock.restart().asSeconds());
    ss<<fps_f;
    fps_text.setString(ss.str());

	window.setView(camera);
	(*ex_ptr).systems.update<render_system>(dtime);

    window.setView(window.getDefaultView());
    window.draw(fps_text);
}

void GameplayStage::release()
{
    fps_text = sf::Text();
	ex_ptr.reset();
	phisics_ptr.reset();
}

void GameplayStage::input(sf::Event & event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        ResourcesManager::getInstanceRef().lvl_set_stage.set();
}
