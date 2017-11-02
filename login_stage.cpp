#include "login_stage.h"
#include "ResourceManager.h"


login_stage::login_stage()
{
}

bool login_stage::init()
{
	auto& resource = ResourcesManager::getInstanceRef();

	loginShowStr = "Login: ";
	loginTxt.setFont(resource.font);
	loginTxt.setString(loginShowStr);
	loginTxt.setPosition(sf::Vector2f(resource.window.getSize().x / 2 - resource.window.getSize().x / 11, resource.window.getSize().y / 2 - resource.window.getSize().y /15));
	
	passShowStr = "Password: ";
	passTxt.setFont(resource.font);
	passTxt.setString(passShowStr);
	passTxt.setPosition(sf::Vector2f(resource.window.getSize().x / 2 - resource.window.getSize().x /11 , resource.window.getSize().y / 2 + resource.window.getSize().y / 15));

	ipShowStr = "Ip: 192.168.0.1";
	ipStr = "192.168.0.1";
	ipTxt.setFont(resource.font);
	ipTxt.setString(ipShowStr);
	ipTxt.setPosition(sf::Vector2f(resource.window.getSize().x / 2 - resource.window.getSize().x / 11, resource.window.getSize().y / 2 + 4*resource.window.getSize().y / 15));

	return true;
}

void login_stage::input(sf::Event & event)
{
	textArregement(event);
	keyArregement(event);
	
}
void login_stage::boldTxt()
{
	loginTxt.setScale(sf::Vector2f(1, 1));
	passTxt.setScale(sf::Vector2f(1, 1));
	ipTxt.setScale(sf::Vector2f(1, 1));
	if (actionCode == 0)
	{
		loginTxt.setScale(sf::Vector2f(1.3, 1.3));
		//std::cout << "0" << std::endl;
	}
	else if (actionCode == 1)
	{
		//std::cout << "1" << std::endl;
		passTxt.setScale(sf::Vector2f(1.3, 1.3));
	}
	else if (actionCode == 2)
	{
		//std::cout << "2" << std::endl;
		ipTxt.setScale(sf::Vector2f(1.3, 1.3));
	}
}

void login_stage::keyArregement(sf::Event & event)
{
	//std::cout << "key pr2" << std::endl;
	if (event.type == sf::Event::KeyPressed)
	{
		//std::cout << "key pr1" << std::endl;
		if (event.key.code == sf::Keyboard::Up)
		{
			if (actionCode != 0)
				--actionCode;
			else
				actionCode = 2;
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			if (actionCode != 2)
				++actionCode;
			else
				actionCode = 0;
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			if (actionCode < 2)
			{
				++actionCode;
			}
			else
			{
				if (!connect())
				{
					
				}
			}
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			ResourcesManager::getInstanceRef().menu_stage.set();
		}
	}
}
bool login_stage::connect()
{
	auto & resource = ResourcesManager::getInstanceRef();
	sf::UdpSocket socket;
	
	sf::UdpSocket::Status status;
	
	//client
	int portSend = 52542;

	//std::cout << "socket: ";

	//std::cin >> port1;
	
	// Send a message to 192.168.?.? on port 556 || ?55002?
	
	//rand the port
	srand(time(NULL));
	do
	{
		resource.portRec = rand() % 40000 + 5000;
	} while (socket.bind(resource.portRec) != sf::UdpSocket::Status::Done);
	std::cout << "portbinded:" << resource.portRec << std::endl;
							
	std::string message = 
		"5555;1;" //5555 is acsess code 
		+ std::to_string(resource.portRec) + ";" + sf::IpAddress::getLocalAddress().toString() + ";" + loginStr + ";" + passStr + ";"; // WPISANY JEST ADRES LOKALNY NIE GLOBALNY !!!!
	
	std::string ip = ipStr;
	resource.ip = ip;
	std::cout << "Sending..." << std::endl;

	std::cout << message << std::endl;

	if (socket.send(message.c_str(), message.size() + 1, ip, portSend) == 0)
	{
		std::cout << "sent " << std::endl;
	}
	else
	{
		std::cout << "not sent (connection problem)" << std::endl;
		socket.unbind();
		return false;
	}
	
	// Receive an answer (most likely from 192.168.1.50, but could be anyone else)
	resource.buffer = { 0 };
	char buffer[1024];
	std::size_t received = 0;
	sf::IpAddress sender, ipHelper;

	// recive message
	socket.setBlocking(false);

	sf::Time time = sf::Time::Zero;
	sf::Clock clk;
	clk.restart();

	std::cout << "waiting... port:" << socket.getLocalPort() << " "<<resource.portRec <<std::endl;
	unsigned short port = resource.portRec;
	while (socket.receive(buffer, sizeof(buffer), received, sender, port) != sf::Socket::Done || sender.toString() == "0.0.0.0" )
	{
		if (time.asSeconds() > 2)
		{
			socket.unbind();
			return false;
		}
		time += clk.restart();
	}
	std::cout << "port to bindee:" << resource.portRec << std::endl;
	socket.unbind();
	//
	resource.buffer = buffer;

	std::cout << sender.toString() << " said: " << resource.buffer << std::endl;

	if (resource.buffer[0] == '0' || resource.buffer.size() < 2)
	{
		return false;
	}

	ResourcesManager::getInstanceRef().creator_stage_multi.set();
	std::cout << "port to bindee:" << resource.portRec << std::endl;
	return true;
}

void login_stage::textArregement(sf::Event & event)
{
	auto& resource = ResourcesManager::getInstanceRef();

	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128)
		{
			//std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
			if (actionCode == 0)
			{
				if (event.text.unicode == 8 && loginShowStr.size() > 7) // 8 - backspace code  7- minimal lenght
				{
					loginShowStr.pop_back();
					loginStr.pop_back();
				}
				else if (loginStr.size() < 25 && event.text.unicode > 32) // ascii > 32 whitespaces
				{
					loginStr.push_back(static_cast<char>(event.text.unicode));
					loginShowStr.push_back(static_cast<char>(event.text.unicode));
				}

				loginTxt.setString(loginShowStr);
			}
			else if (actionCode == 1)
			{
				if (event.text.unicode == 8 && passShowStr.size() > 10) //8 - backspace code 10 minimal lenght
				{
					passShowStr.pop_back();
					passStr.pop_back();
				}
				else if (passStr.size() < 30 && event.text.unicode > 32)// ascii > 32 whitespaces
				{
					passStr.push_back(static_cast<char>(event.text.unicode));
					passShowStr.push_back('*');
				}
				passTxt.setString(passShowStr);
			}
			else if (actionCode == 2)
			{
				if (event.text.unicode == 8 && ipShowStr.size() > 4) //8 - backspace code 10 minimal lenght
				{
					ipShowStr.pop_back();
					ipStr.pop_back();
				}
				else if (ipStr.size() < 30 && event.text.unicode > 32)// ascii > 32 whitespaces
				{
					ipStr.push_back(static_cast<char>(event.text.unicode));
					ipShowStr.push_back(static_cast<char>(event.text.unicode));
				}
				ipTxt.setString(ipShowStr);
			}
		}
	}
}

bool login_stage::update(float dt)
{
	boldTxt();
	return true;
}

void login_stage::render(sf::RenderWindow & window)
{
	//
	window.clear(sf::Color::Black);
	//
	window.draw(loginTxt);
	window.draw(passTxt);
	window.draw(ipTxt);
}

void login_stage::release()
{
	loginStr = std::string();
	passStr = std::string();
	loginShowStr = std::string();
	passShowStr = std::string();
}


login_stage::~login_stage()
{
}
