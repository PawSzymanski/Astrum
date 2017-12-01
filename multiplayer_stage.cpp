#include "multiplayer_stage.h"
#include "ResourceManager.h"


multiplayer_stage::multiplayer_stage() :time(sf::Time::Zero)
{
	ex_ptr = std::make_unique<entityx::EntityX>();
	(*ex_ptr).events.subscribe<ApplyForceEvent>(*this);
}

bool multiplayer_stage::init()
{
	auto &resource = ResourcesManager::getInstanceRef();

	unsigned short  portt = resource.portRec;

	std::cout << "port to bind:" << portt << std::endl;
	socket.bind(portt);
	//system("pause");

	
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


	sendMessage();
	std::cout << " init" << std::endl;
	return true;
}

void multiplayer_stage::input(sf::Event & event)
{
	
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			ResourcesManager::getInstanceRef().login_stage.set();
		}
		
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

	//std::cout << "Sending..." << std::endl;

	//std::cout << ResourcesManager::getInstanceRef().buffer << std::endl;

	if (socket1.send(ResourcesManager::getInstanceRef().buffer.c_str(), ResourcesManager::getInstanceRef().buffer.size() + 1, ResourcesManager::getInstanceRef().ip, port) == 0)
	{
		//std::cout << "sent " << std::endl;
	}
	else
	{
		std::cout << "not sent (connection problem)" << std::endl;
		return false;
	}
	//system("pause");
	return true;
}

bool multiplayer_stage::reciveMessage()
{
	auto & resource = ResourcesManager::getInstanceRef();

	char buffer[1024] = {0};

	std::size_t received;
	sf::Clock clk;
	
	sf::IpAddress sender ;

	//std::cout << "port to bind:" << resource.portRec << std::endl;
	
	unsigned short port = resource.portRec;// because of reference of method socket.receive(... , &port)
	
	socket.setBlocking(false);
	
	//std::cout << "waiting for serwer message..." << std::endl;
	sf::Socket::Status mStatus;
	while ("5555" != resource.decodeOneLineRead(buffer))
	{
		mStatus = socket.receive(buffer, sizeof(buffer), received, sender, port);
	}
	sf::Time time = sf::Time::Zero;
	clk.restart();
	if(mStatus  != sf::Socket::Done || sender.toString() == "0.0.0.0" || "5555"!=resource.decodeOneLineRead(buffer))
	{
		//if (time.asMilliseconds() > 50)
			std::cout << "no serwer message:" << buffer << "sender:"<< sender <<"Status:" << mStatus << std::endl;
		//	sendMessage();
		//	time = sf::Time::Zero;
		//time += clk.restart();
	}
	else 
	{
		//std::cout << "early message received:" << buffer <<"size:" << received << std::endl;
		resource.buffer = buffer;
	}
	
	//std::cout << std::endl;
	//std::cout << resource.buffer << std::endl;
	return true;
}
void multiplayer_stage::updatePartsActions()
{ 
	auto & resource = ResourcesManager::getInstanceRef();
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

bool multiplayer_stage::addPlayer()
{
	auto & resource = ResourcesManager::getInstanceRef();
	PlayersInfo newPlayer;
	auto playerEn = (*ex_ptr).entities.create();
	std::cout << "add pl1:" << resource.buffer << std::endl;
	while ( "" != resource.decodeOneLineRead(resource.buffer))
	{
		isPlayer::Handle playerH;
		for (auto entityPl : (*ex_ptr).entities.entities_with_components(playerH))
		{
			std::cout << "playersID:" << playerH->ID << std::endl;
			if (playerH->ID == 0)
			{
				playerH->ID = thisPlayerId;
			}
		}

		if (players.empty())
		{
			newPlayer.entity = playerEn;

			newPlayer.iD = stoi(resource.decodeOneLineDel(resource.buffer));
			newPlayer.bodyname = resource.decodeOneLineDel(resource.buffer);
			newPlayer.pos.x = stof(resource.decodeOneLineDel(resource.buffer));
			newPlayer.pos.y = stof(resource.decodeOneLineDel(resource.buffer));
			newPlayer.rot = stof(resource.decodeOneLineDel(resource.buffer));
			players.push_back(newPlayer);
			//resource.decodeOneLineDel(resource.buffer); //because of ";;" at the end of string
			std::cout << "empty" << std::endl;
			std::cout << "new->" << newPlayer.iD << "::thid->" << thisPlayerId << " " << newPlayer.bodyname << " " << newPlayer.pos.x << " " << newPlayer.pos.y << " " << newPlayer.rot << std::endl;
			if (newPlayer.iD != thisPlayerId)
			{
				std::cout << "entity add" << std::endl;
				playerEn.assign<isPlayer>(newPlayer.iD);
				playerEn.assign<DontCollideWith>(2);
				(*phisics_ptr).createPolygon(playerEn, newPlayer.pos, sf::Vector2f(0, 0), newPlayer.rot, 1, newPlayer.bodyname);
			}
			std::cout << "add pl2:" << resource.buffer << std::endl;
		}
		else
		{
			for (auto p : players)
			{
				if (p.iD == stoi(resource.decodeOneLineRead(resource.buffer)))
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
					players.push_back(newPlayer);
					//resource.decodeOneLineDel(resource.buffer); //because of ";;" at the end of string
					std::cout <<"new->"<< newPlayer.iD << "::thid->" << thisPlayerId <<" "<< newPlayer.bodyname << " " << newPlayer.pos.x << " " << newPlayer.pos.y << " " << newPlayer.rot << std::endl;
					if (newPlayer.iD != thisPlayerId)
					{
						std::cout << "entity add" << std::endl;
						playerEn.assign<isPlayer>(newPlayer.iD);
						playerEn.assign<DontCollideWith>(2);
						(*phisics_ptr).createPolygon(playerEn, newPlayer.pos, sf::Vector2f(0, 0), newPlayer.rot, 1, newPlayer.bodyname);
					}
					std::cout << "add pl2:" << resource.buffer << std::endl;
						
				}
			}
		}

		std::cout << "player added" <<players[0].iD <<" "<< players[1].iD <<std::endl;
		//system("pause");
	}
	resource.decodeOneLineRead(resource.buffer); //delete ";;"
	return true;
}


bool multiplayer_stage::setPositonOfPlayers()
{
	auto & resource = ResourcesManager::getInstanceRef();
	unsigned int iDSent;
	float rotSent;
	sf::Vector2f posSent, velSent;
	while(resource.decodeOneLineRead(resource.buffer) != "")
	{
		iDSent = stoi(resource.decodeOneLineDel(resource.buffer));
		posSent.x = stof(resource.decodeOneLineDel(resource.buffer));
		posSent.y = stof(resource.decodeOneLineDel(resource.buffer));
		velSent.x = stof(resource.decodeOneLineDel(resource.buffer));
		velSent.y = stof(resource.decodeOneLineDel(resource.buffer));
		rotSent = stof(resource.decodeOneLineDel(resource.buffer));
		
		Position::Handle posH;
		Rotation::Handle rotH;
		isPlayer::Handle isPlayerH;
		Transform::Handle transH;
		LinearVelocity::Handle linVelH;
		//for (auto en : (*ex_ptr).entities.entities_with_components<>(isPlayerH))
		//{
			//std::cout << isPlayerH->ID << ":::::" << iDSent << std::endl;
		//}
		for (auto en : (*ex_ptr).entities.entities_with_components<>(posH, rotH, isPlayerH, transH, linVelH))
		{
			//std::cout << isPlayerH->ID <<" "<< iDSent << std::endl;
			if (isPlayerH->ID == iDSent)
			{
				//std::cout << "pos set:" << posH->pos.x << " " << posH->pos.y << std::endl;
				posH->pos = posSent;
				linVelH->vel = velSent;
				rotH->degree = rotSent;
				transH->trans  ={	1,0,0,
									0,1,0,
									0,0,1 };
				transH->trans.translate(posSent);
				transH->trans.rotate(rotSent);
			}
		}
	}
	resource.decodeOneLineDel(resource.buffer); //to clear ";;" in buffer !IMPORTANT! 
	return true;
}

bool multiplayer_stage::update(float dt)
{
	time += clock.restart();
	dt = 0.05;
	
	if (time.asSeconds() >= dt)
	{
		reciveMessage();
		//case
		auto & resource = ResourcesManager::getInstanceRef();
		int session;

		std::string serwerPass;
		//std::cout <<"recived:" <<resource.buffer << std::endl;
		//system("pause");
		if (resource.decodeOneLineRead(resource.buffer) == "5555")
		{
			serwerPass = resource.decodeOneLineDel(resource.buffer);
			session = stoi(resource.decodeOneLineDel(resource.buffer));
			thisPlayerId = stoi(resource.decodeOneLineDel(resource.buffer));

			//std::cout <<"buffer:" <<resource.buffer << "thisPlayerId:"<< thisPlayerId <<std::endl;
			//system("pause");

			std::string actionCode = "NULL";//resource.decodeOneLineDel(resource.buffer);
			
			while (!resource.buffer.empty())
			{
				//std::cout << "in while:" << resource.buffer << std::endl;
				actionCode = resource.decodeOneLineDel(resource.buffer);
				//std::cout << "action Code:" << actionCode << std::endl;
				if (actionCode == "$1")
				{
					addPlayer();
				}
				else if (actionCode == "$2")
				{
					setPositonOfPlayers();
				}
				else if (actionCode == "$3")
				{

				}
				else if (actionCode == "$4")
				{

				}
			}

			resource.buffer = serwerPass + ";" + std::to_string(session) + ";" + std::to_string(thisPlayerId) + ";" + resource.buffer;
			//std::cout << "AFTER EVERYTHING:" << resource.buffer << std::endl;
		}
		(*phisics_ptr).update(dt);

		//asking server for info players
		if (players.empty())
		{
			resource.buffer = resource.buffer + "#3;;";
		}
		else
		{
			updatePartsActions();
		}

		sendMessage();
		////////////////////////
		time -= sf::seconds(dt);
	}
	
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

	//system("pause");
	return true;
}

void multiplayer_stage::render(sf::RenderWindow & window)
{
	window.setView(ResourcesManager::getInstanceRef().camera);

	(*ex_ptr).systems.update<render_system>(0.01);
	//std::cout << "render" << std::endl;
}

void multiplayer_stage::receive(const ApplyForceEvent & ev)
{
	if ((ev.en.has_component<isPlayer>()))
	{
		auto & res = ResourcesManager::getInstanceRef();
		res.buffer = res.buffer + "#1" + ";" + std::to_string(ev.point.x) + ";" + std::to_string(ev.point.y) + ";" + 
					std::to_string(ev.force.x) + ";" + std::to_string(ev.force.y) + ";"+
					std::to_string(ev.posAftCorr.x) + ";" + std::to_string(ev.posAftCorr.y) + ";";
		//std::cout << res.buffer << std::endl;
		//std::cout << "^ recived ^" << std::endl;
	}
}

void multiplayer_stage::release()
{
	socket.unbind();
	std::cout << "release unbind" << std::endl;
}


multiplayer_stage::~multiplayer_stage()
{
}
