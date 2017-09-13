#include "GameplayStage.h"
#include "ResourceManager.h"

GameplayStage::GameplayStage(Container &cont) : gravity(0.0f, 2.0f/*   9.8   */), vertCont(cont)
{
	display_fps_time = sf::Time::Zero;
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

	ResourcesManager::getInstanceRef().areAllPlatfIncluded = false;

	(*ex_ptr).systems.add<player_input_system>(*phisics_ptr);
	(*ex_ptr).systems.update<player_input_system>(dtime);


	(*ex_ptr).systems.add<engine_system>((*ex_ptr).events, *phisics_ptr);
	(*ex_ptr).systems.add<render_system>(window);
    (*ex_ptr).systems.add<DestructionSystem>(*ex_ptr);
    (*ex_ptr).systems.add<CraneSystem>(*ex_ptr, *phisics_ptr);
	(*ex_ptr).systems.add<platform_manager>((*ex_ptr).events);
	(*ex_ptr).systems.add<animations_system>();
    (*ex_ptr).systems.add<CargoSystem>();
	(*ex_ptr).systems.add<game_over_system>();
	(*ex_ptr).systems.add<enemy_system>((*ex_ptr),*phisics_ptr);


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

	(*phisics_ptr).update(dt);

	(*ex_ptr).systems.update<game_over_system>(dt);

	(*ex_ptr).systems.update<engine_system>(dt);
    (*ex_ptr).systems.update<DestructionSystem>(dt);
    (*ex_ptr).systems.update<CraneSystem>(dt);
	(*ex_ptr).systems.update<platform_manager>(dt);
	(*ex_ptr).systems.update<animations_system>(dt);
    (*ex_ptr).systems.update<CargoSystem>(dt);
	(*ex_ptr).systems.update<enemy_system>(dt);

	return true;
}

void GameplayStage::render(sf::RenderWindow &window)
{
	//FPS clock
	static sf::Clock fps_clock, display_fps_clock;;

    std::stringstream ss;

	const float dt = 0.1;
	display_fps_time += display_fps_clock.restart();
	float fps_f = (1.0f / fps_clock.restart().asSeconds());
	if (display_fps_time.asSeconds() >= dt)
	{
		display_fps_time = sf::Time::Zero;
		
		ss << fps_f;
		fps_text.setString(ss.str());
	}
	//


	window.setView(camera);
	//draw gameplay
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
	if (event.type == sf::Event::MouseButtonReleased)
	{
		ResourcesManager::getInstanceRef().isMouseButtonReleased = true;
	}
	else
	{
		ResourcesManager::getInstanceRef().isMouseButtonReleased = false;
	}
}
