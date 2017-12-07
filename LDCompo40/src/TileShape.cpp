#include "TileShape.h"

#include "Globals.h"

#include <fstream>
#include <iostream>

TileShape::TileShape()
{
}

TileShape::~TileShape()
{
}

void TileShape::init(std::string dataFile, sf::Vector2i position)
{
	m_position = position;

	std::ifstream file(dataFile);

	int width = 0;
	int height = 0;
	int counter = 0;

	char currentChar;
	while (file)
	{
		if (file.peek() == '\n')
		{
			width = counter;
			counter = 0;
		}

		if (counter == 0)
			height++;

		counter++;

		file >> currentChar;
		
		m_shapeData.push_back(currentChar);
	}

	m_width = width;
	m_height = height;

	/*m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_width * m_height);

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;

			if (m_shapeData[index] == '0')
				continue;

			sf::Vector2f position1(m_position.x + (x * TILE_SIZE),				m_position.y + (y * TILE_SIZE));
			sf::Vector2f position2(m_position.x + ((x* TILE_SIZE) + TILE_SIZE),	m_position.y + (y * TILE_SIZE));
			sf::Vector2f position3(m_position.x + ((x* TILE_SIZE) + TILE_SIZE),	m_position.y + ((y * TILE_SIZE) + TILE_SIZE));
			sf::Vector2f position4(m_position.x + (x* TILE_SIZE),				m_position.y + ((y * TILE_SIZE) + TILE_SIZE));

			m_vertices.append(sf::Vertex(position1, sf::Color::Green));
			m_vertices.append(sf::Vertex(position2, sf::Color::Green));
			m_vertices.append(sf::Vertex(position3, sf::Color::Green));
			m_vertices.append(sf::Vertex(position4, sf::Color::Green));
		}
	}*/
}

void TileShape::update(World& world)
{
	// reset old position, should save the old mapDAta!
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;

			if (m_shapeData[index] == '0')
				continue;

			world.getMapData()[(m_position.y + y) * WORLD_WIDTH + (m_position.x + x)] = TileType::EMPTY;
		}
	}

	//update position
	//m_position.x += 1;
	
	// draw on new position
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;

			if (m_shapeData[index] == '0')
				continue;

			world.getMapData()[(m_position.y + y) * WORLD_WIDTH + (m_position.x + x)] = TileType::VIRUS_UNIT;
		}
	}
}

/*void TileShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(m_vertices, states);
}*/