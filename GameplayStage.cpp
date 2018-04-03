#include "GameplayStage.h"
#include "ResourceManager.h"

GameplayStage::GameplayStage(Container &cont) : gravity(0.0f, 2.0f/*   9.8   */), vertCont(cont), cameraX(0), cameraY(0)
{
	display_fps_time = sf::Time::Zero;
}

GameplayStage::~GameplayStage()
{
	release();
}

void GameplayStage::updateCamera()
{
	auto &resource = ResourcesManager::getInstanceRef();

	if (!ResourcesManager::getInstanceRef().isMovingCameraOn)
	{
		resource.camera.reset(sf::FloatRect(0, 0, 17.5, 10));
		return;
	}
	//move camera if needed
	for (auto en : (*ex_ptr).entities.entities_with_components<isPlayer>())
	{
		sf::FloatRect fRect;
		Position::Handle pos = en.component<Position>();
		//std::cout << "player.x :  " << pos->pos.x << "cam x : " << camera.getCenter().x << std::endl;
		if (resource.camera.getCenter().x - pos->pos.x > CAMERA_CONST_X)
		{
			resource.camera.move(sf::Vector2f((pos->pos.x + CAMERA_CONST_X - resource.camera.getCenter().x) ,0));
			//std::cout << "in" << std::endl;
		}
		else if (resource.camera.getCenter().x - pos->pos.x < -CAMERA_CONST_X)
		{
			resource.camera.move(sf::Vector2f((pos->pos.x - resource.camera.getCenter().x - CAMERA_CONST_X), 0));
		}
		if (resource.camera.getCenter().y - pos->pos.y > CAMERA_CONST_Y)
		{
			resource.camera.move(sf::Vector2f(0,(pos->pos.y + CAMERA_CONST_Y - resource.camera.getCenter().y)));
			//std::cout << "in" << std::endl;
		}
		else if (resource.camera.getCenter().y - pos->pos.y < -CAMERA_CONST_Y)
		{
			resource.camera.move(sf::Vector2f(0, (pos->pos.y - resource.camera.getCenter().y - CAMERA_CONST_Y)));
		}
	}
}

bool GameplayStage::init()
{
	
	ex_ptr = std::make_unique<entityx::EntityX>();
	phisics_ptr = std::make_unique<Phisics_2D>((*ex_ptr), vertCont, gravity);
	(*phisics_ptr).init();

	auto &window = ResourcesManager::getInstanceRef().window;
	auto &resource = ResourcesManager::getInstanceRef();

	resource.camera.reset(sf::FloatRect(0, 0, 17.5, 10));									//camera 

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
	(*ex_ptr).systems.add<sliding_doors_system>();


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
	(*ex_ptr).systems.update<sliding_doors_system>(dt);

	return true;
}
//void fps_clock
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
	window.setView(ResourcesManager::getInstanceRef().camera);
	//draw gameplay
	(*ex_ptr).systems.update<render_system>(dtime);

    window.setView(window.getDefaultView());
	//draw fps
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
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Equal)
		{
			ResourcesManager::getInstanceRef().camera.zoom(100);
		}
		else if (event.key.code == sf::Keyboard::Dash)
		{
			ResourcesManager::getInstanceRef().camera.zoom(-1);
		}
	}
	else
	{
		ResourcesManager::getInstanceRef().isMouseButtonReleased = false;
	}
}
