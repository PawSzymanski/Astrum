/*
 *  creatorstage.cpp
 *
 *  Created: 2017-07-07
 *   Author: Patryk Wojtanowski modified by Pawe³ Szymañski
 */

#include "creatorstageMulti.h"
#include "ResourceManager.h"

CreatorStageMulti::CreatorStageMulti()
{

}
//sending the buffer from resource

bool CreatorStageMulti::sendMessageToSerwer()
{
	sf::UdpSocket socket;
	sf::UdpSocket::Status status;
	unsigned short port = 52542;

	std::cout << "Sending..." << std::endl;

	std::cout << ResourcesManager::getInstanceRef().buffer << std::endl;

	if (socket.send(ResourcesManager::getInstanceRef().buffer.c_str(), ResourcesManager::getInstanceRef().buffer.size() + 1, ResourcesManager::getInstanceRef().ip, port) == 0)
	{
		std::cout << "sent " << std::endl;
	}
	else
	{
		std::cout << "not sent (connection problem)" << std::endl;
		return false;
	}

	return true;
}

bool CreatorStageMulti::reciveMessageFromSerwer()
{
	auto & resource = ResourcesManager::getInstanceRef();
	resource.buffer = { 0 };
	sf::UdpSocket socket;
	std::size_t received;
	std::cout << "port to bind:" << resource.portRec << std::endl;
	socket.bind(resource.portRec);
	//socket.setBlocking(false);
	sf::IpAddress sender;
	sf::Time time = sf::Time::Zero;
	sf::Clock clk;
	clk.restart();
	char buffer[1024];
	std::cout << "waiting for serwer message..." << std::endl;
	unsigned short port = resource.portRec; // because of reference of method socket.receive(... , &port)
	while (socket.receive(buffer, sizeof(buffer), received, sender, port) != sf::Socket::Done || sender.toString() == "0.0.0.0")
	{
		if (time.asSeconds() > 4)
		{
			std::cout << "no serwer message:"<<buffer  << std::endl;
			socket.unbind();
			return false;
		}
		time += clk.restart();
	}
	socket.unbind();
	resource.buffer = buffer;
	std::cout << std::endl;
	std::cout << resource.buffer << std::endl;
	
	return true;
}



bool CreatorStageMulti::init()
{
    auto& resource = ResourcesManager::getInstanceRef();

    next = nullptr;

    esc_text.setCharacterSize(32);
    esc_text.setFillColor(sf::Color::White);
    esc_text.setPosition(50,50);
    esc_text.setFont(resource.font);
    esc_text.setString("Lvl set:  ESC");

    mask_rect.setFillColor(sf::Color::Black);
    mask_rect.setPosition(sf::Vector2f(0,0));
    mask_rect.setSize(sf::Vector2f(1400,800));

    fade_in = true;
    fade_out = false;
    timer = 1.0f;

    std::string bodynames[3] = { "Mk. I" , "Mk. II", "Mk. III" };
    std::string partnames[5] = { "large eng.", "small eng.", "langing legs", "crane", "gun" };
	std::string garageNames[4] = { "1 garage", "2 garage" ,"3 garage" ,"4 garage" };
    int bodyposition = 500;
    int partposition = 150;
	int garagePositionY = 130;
    auto &container = ResourcesManager::getInstanceRef().vertCont;
    std::string bodys[3] = {
        "TRIANGLE_BODY",
        "LONG_BODY",
        "COBRA_BODY"
	};

	std::string parts[5] = {
		"large_engine",
		"small_engine",
		"landing_legs",
		"crane",
		"gun"
    };

    for(int i=0; i<3; ++i)
    {
        bodybuttons[i].init(sf::Vector2f(bodyposition,50), bodynames[i], resource.font, bodys[i]);
        bodyposition += 120;
    }

    for(int i=0; i<5; ++i)
    {
        partbuttons[i].init(sf::Vector2f(1200,partposition), partnames[i], resource.font, parts[i]);
        partposition += 120;
    }
	for (int i = 0; i < 4; ++i)
	{
		garageButtons[i].init(sf::Vector2f(100, garagePositionY), garageNames[i], resource.font, bodys[3]);
		garagePositionY += 110;
	}

    start_button.init(resource.font,32, sf::Vector2f(150,670),sf::Color::White, "START", sf::Vector2f(40,15));
    save_button.init(resource.font,32, sf::Vector2f(150,600),sf::Color::White, "SAVE", sf::Vector2f(40,15));

    manager.init();

    return true;
}

void CreatorStageMulti::input(sf::Event &event)
{
	start_button.rect.setOutlineThickness(8);
	save_button.rect.setOutlineThickness(8);
	if ("5555" != ResourcesManager::getInstanceRef().decodeOneLineRead(ResourcesManager::getInstanceRef().buffer))
	{
		ResourcesManager::getInstanceRef().buffer = "5555;"+ ResourcesManager::getInstanceRef().buffer;
	}
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            next = &(ResourcesManager::getInstanceRef().login_stage);
            fade_out = true;
            fade_in = false;
        }
        else if(event.key.code == sf::Keyboard::Return)
        {
            if(!manager.is_body_set())
                return;

            manager.saveShip( ResourcesManager::getInstanceRef().shipInfoMulti);
			if (sendMessageToSerwer() && reciveMessageFromSerwer())
			{
				next = &(ResourcesManager::getInstanceRef().multi_stage);
				fade_out = true;
				fade_in = false;
			}
        }
    }
	// loading things to garage
	for (int i = 0; i < 4; ++i)
	{
		if (garageButtons[i].input(event))
		{
			std::string & str = (ResourcesManager::getInstanceRef().shipInfoMulti);
			
			str = "resources/levelData/ship_" + std::to_string(i + 1) + ".cfg";
			
			manager.loadPartFromFile(str);
		}
	}
	//
    for(int i=0; i<3; ++i)
        if(bodybuttons[i].input(event) && manager.parts.size() < 1)
           manager.set_body(bodybuttons[i].getName());
    for(int i=0; i<5; ++i)
        if(partbuttons[i].input(event))
           manager.add_part(partbuttons[i].getName());

    if(start_button.input(event))
    {
        if(!manager.is_body_set())
            return;

      manager.saveShip(ResourcesManager::getInstanceRef().shipInfoMulti);

	  if (sendMessageToSerwer() && reciveMessageFromSerwer())
	  {
		  next = &(ResourcesManager::getInstanceRef().multi_stage);
		  fade_out = true;
		  fade_in = false;
	  }
    }

    if(save_button.input(event))
        manager.saveShip( ResourcesManager::getInstanceRef().shipInfoMulti);

    manager.input(event);
}

bool CreatorStageMulti::update(float dt)
{
	if(fade_in)
    {
        sf::Color col = mask_rect.getFillColor();
        col.a = timer * 255.0f;
        mask_rect.setFillColor(col);
        timer -= dt;
        fade_in = (timer >=0);
    }

    if(fade_out)
    {
        sf::Color col = mask_rect.getFillColor();
        col.a = timer * 255.0f;
        mask_rect.setFillColor(col);
        timer += dt;
        fade_out = (timer < 1.f);
    }

    if(next && !fade_out)
        next->set();

    for(int i=0; i<3; ++i)
        bodybuttons[i].update(dt);
    for(int i=0; i<5; ++i)
        partbuttons[i].update(dt);
	for (int i = 0; i<4; ++i)
		garageButtons[i].update(dt);

    //std::cout<<"fade_in "<<fade_in<<std::endl;
    //std::cout<<"fade_out "<<fade_out<<std::endl;
    return true;
}

void CreatorStageMulti::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    window.draw(esc_text);

    for(int i=0; i<3; ++i)
        window.draw(bodybuttons[i]);
    for(int i=0; i<5; ++i)
        window.draw(partbuttons[i]);
	for (int i = 0; i < 4; ++i)
		window.draw(garageButtons[i]);

    window.draw(start_button);
    window.draw(save_button);
    window.draw(manager);
    window.draw(mask_rect);
}

void CreatorStageMulti::release()
{
    next = nullptr;
    for(int i=0; i<3; ++i)
        bodybuttons[i].release();
    for(int i=0; i<5; ++i)
        partbuttons[i].release();
	for (int i = 0; i < 4; ++i)
		garageButtons[i].release();

    start_button.release();
    save_button.release();
    manager.release();

    esc_text = sf::Text();
}
