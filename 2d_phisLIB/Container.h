#pragma once
#include <vector>
#include <cmath>
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

class Container
{
public:
	Container();
	int textureNumber;

	std::vector<sf::VertexArray> vertexArrays;
	std::vector<std::vector<sf::Vector2f>> normals;
	std::vector<sf::Texture> textures;
    std::map <std::string, int> indexes;
	std::map <std::string, int> textureIndexesMap;


    void addPoly(sf::VertexArray & v, int size, std::string name);
	void addTexture(sf::Texture texture, std::string vertexName);
    sf::VertexArray & getPoly(const std::string& name);
    std::vector <sf::Vector2f> & getNormals(const std::string& name);
	sf::Texture & getTexture(std::string texture);

	~Container();
};

