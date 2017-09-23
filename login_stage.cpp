#include "login_stage.h"
#include "ResourceManager.h"


login_stage::login_stage()
{
}

bool login_stage::init()
{
	auto& resource = ResourcesManager::getInstanceRef();

	loginStr = "Login: ";
	loginTxt.setFont(resource.font);
	loginTxt.setString(loginStr);
	loginTxt.setPosition(sf::Vector2f(resource.window.getSize().x / 2 - resource.window.getSize().x / 11, resource.window.getSize().y / 2 - resource.window.getSize().y /15));
	
	passShowStr = "Password: ";
	passTxt.setFont(resource.font);
	passTxt.setString(passShowStr);
	passTxt.setPosition(sf::Vector2f(resource.window.getSize().x / 2 - resource.window.getSize().x /11 , resource.window.getSize().y / 2 + resource.window.getSize().y / 15));

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
	if (actionCode == 0)
	{
		loginTxt.setScale(sf::Vector2f(1.3, 1.3));
		std::cout << "0" << std::endl;
	}
	else if (actionCode == 1)
	{
		std::cout << "1" << std::endl;
		passTxt.setScale(sf::Vector2f(1.3, 1.3));
	}
}

void login_stage::keyArregement(sf::Event & event)
{
	//std::cout << "key pr2" << std::endl;
	if (event.type == sf::Event::KeyPressed)
	{
		//std::cout << "key pr1" << std::endl;
		if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
		{
			std::cout << "key pr" << std::endl;
			if (actionCode == 0)
			{
				actionCode = 1;
			}
			else if (actionCode == 1)
			{
				actionCode = 0;
			}
			/*switch (actionCode)
			{
			case 0:
			
				actionCode = 1;
			break;
			case 1:
			
				actionCode = 0;
			break;
			default:
				break;
			}*/
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			if (!actionCode)
			{
				actionCode = 1;
			}
			else
			{
				connect();
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
	/*try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;

		/* Create a connection 
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "lele", "");
		/* Connect to the MySQL test database 
		system("pause");
		con->setSchema("firstsql");

		stmt = con->createStatement();
		stmt->execute("DROP TABLE IF EXISTS firstsql");

		delete stmt;

		/* '?' is the supported placeholder syntax */
		//pstmt = con->prepareStatement("INSERT INTO position(id) VALUES (?)");
		//for (int i = 1; i <= 10; i++) {
		//	pstmt->setInt(1, i);
		//	pstmt->executeUpdate();
		//}
		//delete pstmt;

		/* Select in ascending order 
		//pstmt->add_country();
		pstmt = con->prepareStatement("SELECT xDim FROM position ");
		res = pstmt->executeQuery();

		/* Fetch in reverse = descending order! 
		res->afterLast();

		delete res;

		delete pstmt;
		delete con;

	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line "
			<< __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() <<
			" )" << std::endl;
		return false;
	}
	*/

	ResourcesManager::getInstanceRef().multi_stage.set();
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
				if (event.text.unicode == 8 && loginStr.size() > 7) // 8 - backspace code  7- minimal lenght
				{
					loginStr.pop_back();
				}
				else if (loginStr.size() < 25 && event.text.unicode > 32) // ascii > 32 whitespaces
				{
					loginStr.push_back(static_cast<char>(event.text.unicode));
				}

				loginTxt.setString(loginStr);
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
}

void login_stage::release()
{
}


login_stage::~login_stage()
{
}
