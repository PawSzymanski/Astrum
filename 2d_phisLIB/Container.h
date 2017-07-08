#pragma once
#include <vector>
#include <cmath>
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

class Container
{
public:
	Container();

	std::vector<sf::VertexArray> vertexArrays;
	std::vector<std::vector<sf::Vector2f>> normals;
    std::map <std::string, int> indexes;

    void addPoly(sf::VertexArray & v, int size, std::string name);
    sf::VertexArray & getPoly(const std::string& name);
    std::vector <sf::Vector2f> & getNormals(const std::string& name);

	~Container();
};

