#pragma once

#include "World.h"

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Transformable.hpp>

#include <vector>
#include <string>

class TileShape// : public sf::Drawable, public sf::Transformable
{
public:
	TileShape();
	~TileShape();

	void init(std::string dataFile, sf::Vector2i position);
	void update(World& world);
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::VertexArray m_vertices;
	sf::Vector2i m_position;

	std::vector<char> m_shapeData;

	int m_width;
	int m_height;
};