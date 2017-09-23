#pragma once
#include "LibsAndDeclarations.h"
#include "GameStage.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class login_stage : public GameStage
{

	//std::string loginN, passN;
	int actionCode;
	std::string loginStr;
	std::string passStr, passShowStr;
	sf::Text loginTxt, passTxt;

public:
	login_stage();

	virtual bool init() override;
	virtual void input(sf::Event &event) override;
	void boldTxt();
	void keyArregement(sf::Event & event);
	bool connect();
	void textArregement(sf::Event & event);
	virtual bool update(float dt) override;
	virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;

	~login_stage();
};

