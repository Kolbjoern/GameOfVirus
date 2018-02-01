#pragma once

#include "World.h"

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Transformable.hpp>

#include <vector>
#include <string>

class TileShape
{
public:
	TileShape();
	~TileShape();

	void init(std::string dataFile, sf::Vector2i position, World* world);
	void update(float deltaTime);
private:
	World* m_world;

	sf::VertexArray m_vertices;
	sf::Vector2i m_position;

	std::vector<char> m_shapeData;
	std::vector<TileType> m_oldMapData;

	int m_width;
	int m_height;
};