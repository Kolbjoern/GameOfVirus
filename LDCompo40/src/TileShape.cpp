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

void TileShape::init(std::string dataFile, sf::Vector2i position, World* world)
{
	m_position = position;
	m_world = world;

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

	m_oldMapData.resize(m_width * m_height);

	// draw initial position
	
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;
			
			if (m_shapeData[index] == '0')
				continue;

			int worldIndex = (m_position.y + y) * WORLD_WIDTH + (m_position.x + x);

			m_oldMapData[index] = m_world->getMapData()[worldIndex];

			m_world->getMapData()[worldIndex] = TileType::VIRUS;
		}
	}
}

void TileShape::update(float deltaTime)
{
	// reset old position, should save the old mapDAta!
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;
			int worldIndex = (m_position.y + y) * WORLD_WIDTH + (m_position.x + x);

			//if (m_shapeData[index] == '0')
			//	continue;

			if (m_world->getMapData()[worldIndex] == TileType::VIRUS)
			{
				m_shapeData[index] = '1';
				m_world->getMapData()[worldIndex] = m_oldMapData[index];
			}
			else
				m_shapeData[index] = '0';

			//m_world->getMapData()[worldIndex] = m_oldMapData[index];

			//world.getMapData()[(m_position.y + y) * WORLD_WIDTH + (m_position.x + x)] = TileType::EMPTY;
		}
	}

	// draw on new position
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;
			int worldIndex = (m_position.y + y) * WORLD_WIDTH + (m_position.x + x);

			m_oldMapData[index] = m_world->getMapData()[worldIndex];

			if (m_shapeData[index] == '0')
				continue;

			//m_oldMapData[index] = m_world->getMapData()[worldIndex];
			m_world->getMapData()[worldIndex] = TileType::VIRUS;
		}
	}
}