#include "multiplayer_stage.h"
#include "ResourceManager.h"


multiplayer_stage::multiplayer_stage()
{
}

bool multiplayer_stage::init()
{
	auto &resource = ResourcesManager::getInstanceRef();

	unsigned short  portt = resource.portRec;
	socket.bind(portt);

	ex_ptr = std::make_unique<entityx::EntityX>();
	phisics_ptr = std::make_unique<Phisics_2D>((*ex_ptr), resource.vertCont, sf::Vector2f(0.0, 0.0));
	(*phisics_ptr).init();

	auto &window = ResourcesManager::getInstanceRef().window;

	resource.camera.reset(sf::FloatRect(0, 0, 17.5, 10));

	ResourcesManager::getInstanceRef().areAllPlatfIncluded = false;

	(*ex_ptr).systems.add<LoadingThingsToMultiStage>(*phisics_ptr);
	(*ex_ptr).systems.update<LoadingThingsToMultiStage>(0.01);

	(*ex_ptr).systems.add<engine_system>((*ex_ptr).events, *phisics_ptr);
	(*ex_ptr).systems.add<render_system>(window);
	(*ex_ptr).systems.add<DestructionSystem>(*ex_ptr);
	(*ex_ptr).systems.add<CraneSystem>(*ex_ptr, *phisics_ptr);
	(*ex_ptr).systems.add<platform_manager>((*ex_ptr).events);
	(*ex_ptr).systems.add<animations_system>();
	(*ex_ptr).systems.add<CargoSystem>();
	(*ex_ptr).systems.add<game_over_system>();
	(*ex_ptr).systems.add<enemy_system>((*ex_ptr), *phisics_ptr);
	(*ex_ptr).systems.add<sliding_doors_system>();
	std::cout << " init" << std::endl;
	return true;
}

void multiplayer_stage::input(sf::Event & event)
{
	auto & resource = ResourcesManager::getInstanceRef();
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			ResourcesManager::getInstanceRef().login_stage.set();
		}
		partId::Handle partIdH;
		KeyAssigned::Handle keyH;
		//how data looks like:
		//part id;bool/flag;
		resource.buffer = resource.buffer + "#2;";//action code of buffers
		for (auto partEn : (*ex_ptr).entities.entities_with_components(partIdH, keyH))
		{
			if (sf::Keyboard::isKeyPressed(keyH->key))
			{
				resource.buffer = resource.buffer + std::to_string(partIdH->id) + ";" + "1;";
			}
			else
			{
				resource.buffer = resource.buffer + std::to_string(partIdH->id) + ";" + "0;";
			}
		}
		resource.buffer = resource.buffer + ";";
	}
	
}

bool multiplayer_stage::sendMessage()
{
	if (ResourcesManager::getInstanceRef().buffer.size() < 2)
		return false;

	//getting data 
	sf::UdpSocket socket1;
	sf::UdpSocket::Status status;
	unsigned short port = 52542;

	std::cout << "Sending..." << std::endl;

	std::cout << ResourcesManager::getInstanceRef().buffer << std::endl;

	if (socket1.send(ResourcesManager::getInstanceRef().buffer.c_str(), ResourcesManager::getInstanceRef().buffer.size() + 1, ResourcesManager::getInstanceRef().ip, port) == 0)
	{
		//std::cout << "sent " << std::endl;
	}
	else
	{
		std::cout << "not sent (connection problem)" << std::endl;
		return false;
	}
	system("pause");
	return true;
}

bool multiplayer_stage::reciveMessage()
{
	auto & resource = ResourcesManager::getInstanceRef();

	char buffer[1024] = {0};

	
	std::size_t received;
	sf::Clock clk;
	
	sf::IpAddress sender = "192.168.1.8";

	std::cout << "port to bind:" << resource.portRec << std::endl;
	
	unsigned short port = resource.portRec;// because of reference of method socket.receive(... , &port)
	
	socket.setBlocking(false);
	
	//std::cout << "waiting for serwer message..." << std::endl;
	

	sf::Time time = sf::Time::Zero;
	clk.restart();
	if(socket.receive(buffer, sizeof(buffer), received, sender, port) != sf::Socket::Done || sender.toString() == "0.0.0.0" || "5555"!=resource.decodeOneLineRead(buffer))
	{
		//if (time.asMilliseconds() > 50)
			std::cout << "no serwer message:" << buffer << "sender:"<< sender <<std::endl;
		//	sendMessage();
		//	time = sf::Time::Zero;
		//time += clk.restart();
	}
	else 
	{
		std::cout << "early message received:" << buffer <<"size:" << received << std::endl;
		resource.buffer = buffer;
	}
	socket.unbind();
	
	//std::cout << std::endl;
	//std::cout << resource.buffer << std::endl;
	return true;
}

bool multiplayer_stage::addPlayer()
{
	auto & resource = ResourcesManager::getInstanceRef();
	PlayersInfo newPlayer;
	auto playerEn = (*ex_ptr).entities.create();
	std::cout << "add pl1:" << resource.buffer << std::endl;
	while ("" != resource.decodeOneLineRead(resource.buffer))
	{
		if (players.empty())
		{
			newPlayer.entity = playerEn;
			newPlayer.iD = stoi(resource.decodeOneLineDel(resource.buffer));
			newPlayer.bodyname = resource.decodeOneLineDel(resource.buffer);
			newPlayer.pos.x = stof(resource.decodeOneLineDel(resource.buffer));
			newPlayer.pos.y = stof(resource.decodeOneLineDel(resource.buffer));
			newPlayer.rot = stof(resource.decodeOneLineDel(resource.buffer));
			//resource.decodeOneLineDel(resource.buffer); //because of ";;" at the end of string

			playerEn.assign<isPlayer>(newPlayer.iD);
			playerEn.assign<DontCollideWith>(1);
			(*phisics_ptr).createPolygon(playerEn, newPlayer.pos, sf::Vector2f(0, 0), newPlayer.rot, 1, newPlayer.bodyname);
			std::cout << "add pl2:" << resource.buffer << std::endl;
			players.push_back(newPlayer);
		}
		else
		for (auto p : players)
		{
			if (p.iD == stoi(resource.decodeOneLineRead(resource.buffer)) || stoi(resource.decodeOneLineRead(resource.buffer)) == thisPlayerId)
			{
				//delete that part of buffer
				for (int i = 0; i < 5; ++i)
					resource.decodeOneLineDel(resource.buffer);

				continue;
			}
			else
			{
				newPlayer.entity = playerEn;
				newPlayer.iD = stoi(resource.decodeOneLineDel(resource.buffer));
				newPlayer.bodyname = resource.decodeOneLineDel(resource.buffer);
				newPlayer.pos.x = stof(resource.decodeOneLineDel(resource.buffer));
				newPlayer.pos.y = stof(resource.decodeOneLineDel(resource.buffer));
				newPlayer.rot = stof(resource.decodeOneLineDel(resource.buffer));
				//resource.decodeOneLineDel(resource.buffer); //because of ";;" at the end of string

				playerEn.assign<isPlayer>(newPlayer.iD);
				playerEn.assign<DontCollideWith>(1);
				(*phisics_ptr).createPolygon(playerEn, newPlayer.pos, sf::Vector2f(0, 0), newPlayer.rot, 1, newPlayer.bodyname);
				std::cout << "add pl2:" << resource.buffer << std::endl;
				players.push_back(newPlayer);
			}
		}

		std::cout << "player added" << std::endl;
	}
	resource.decodeOneLineRead(resource.buffer); //delete ";;"
	return true;
}

bool multiplayer_stage::setPositonOfPlayer()
{
	auto & resource = ResourcesManager::getInstanceRef();
	unsigned int iDSent;
	float rotSent;
	sf::Vector2f posSent;
	while(resource.decodeOneLineRead(resource.buffer) != "")
	{
		iDSent = stoi(resource.decodeOneLineDel(resource.buffer));
		posSent.x = stof(resource.decodeOneLineDel(resource.buffer));
		posSent.y = stof(resource.decodeOneLineDel(resource.buffer));
		rotSent = stof(resource.decodeOneLineDel(resource.buffer));
		
		Position::Handle posH;
		Rotation::Handle rotH;
		isPlayer::Handle isPlayerH;

		for (auto en : (*ex_ptr).entities.entities_with_components<>(posH, rotH, isPlayerH))
		{
			if (isPlayerH->ID == iDSent)
			{
				posH->pos = posSent;
				rotH->degree = rotSent;
			}
		}
	}
	resource.decodeOneLineDel(resource.buffer); //to clear ";;" in buffer !IMPORTANT! 
	return true;
}

bool multiplayer_stage::update(float dt)
{
	sendMessage();
	reciveMessage();
	//case
	auto & resource = ResourcesManager::getInstanceRef();
	int session; 

	std::string serwerPass;
	std::cout <<"recived:" <<resource.buffer << std::endl;
	system("pause");
	if (resource.decodeOneLineRead(resource.buffer) == "5555")
	{
		serwerPass = resource.decodeOneLineDel(resource.buffer);
		session = stoi(resource.decodeOneLineDel(resource.buffer));
		thisPlayerId = stoi(resource.decodeOneLineDel(resource.buffer));

			std::cout <<"buffer:" <<resource.buffer << "thisPlayerId:"<< thisPlayerId <<std::endl;
			system("pause");

			std::string actionCode = "NULL";//resource.decodeOneLineDel(resource.buffer);

			while (actionCode != "")
			{
				std::cout << "in while:" << resource.buffer << std::endl;
				actionCode = resource.decodeOneLineDel(resource.buffer);

				if (actionCode == "#1")
				{
					addPlayer();
				}
				else if (actionCode == "#2")
				{
					setPositonOfPlayer();
				}
				else if (actionCode == "#3")
				{

				}
				else if (actionCode == "#4")
				{

				}
			}
	resource.buffer = serwerPass + ";" + std::to_string(session) + ";" + std::to_string(thisPlayerId) + ";" + resource.buffer;
	}
	
	(*phisics_ptr).update(dt);
	
	//(*ex_ptr).systems.update<engine_system>(dt);
	//(*ex_ptr).systems.update<DestructionSystem>(dt);
	//(*ex_ptr).systems.update<CraneSystem>(dt);
	//(*ex_ptr).systems.update<platform_manager>(dt);
	//(*ex_ptr).systems.update<animations_system>(dt);
	//(*ex_ptr).systems.update<CargoSystem>(dt);
	//(*ex_ptr).systems.update<game_over_system>(dt);
	//(*ex_ptr).systems.update<enemy_system>(dt);
	//(*ex_ptr).systems.update<sliding_doors_system>(dt);

	//std::cout << "update" << std::endl;
	return true;
}

void multiplayer_stage::render(sf::RenderWindow & window)
{
	window.setView(ResourcesManager::getInstanceRef().camera);

	(*ex_ptr).systems.update<render_system>(0.01);
	//std::cout << "render" << std::endl;
}

void multiplayer_stage::release()
{
	socket.unbind();
}


multiplayer_stage::~multiplayer_stage()
{
}
