#pragma once
#include "LibsAndDeclarations.h"
#include "GameStage.h"
#include "mysql_connection.h"
#include <SFML\Network.hpp>


class login_stage : public GameStage
{

	//std::string loginN, passN;
	int actionCode;
	std::string loginStr, loginShowStr,
		passStr, passShowStr,
		ipStr, ipShowStr;
	 
	sf::Text loginTxt, passTxt, ipTxt;

public:
	login_stage();

	bool connect();

	virtual bool init() override;
	virtual void input(sf::Event &event) override;
	virtual bool update(float dt) override;
	virtual void render(sf::RenderWindow &window) override;
	virtual void release() override;
	
	void boldTxt();
	void keyArregement(sf::Event & event);
	void textArregement(sf::Event & event);

	~login_stage();
};

