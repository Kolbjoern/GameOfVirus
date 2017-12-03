#include "World.h"

#include "utils\RandomNumGen.h"

#include <algorithm>

World::World()
{
}

World::~World()
{
}

void World::init(int tileSize, int width, int height)
{
	m_tileSize = tileSize;
	m_width = width;
	m_height = height;

	m_mapData.resize(width * height);
	m_virusIndices.reserve(width * height);

	m_virusSpreadTimer = 0.0f;
	m_currVirusIteration = 0;
	m_currReactivateVirusIteration = 0;
	m_currentlyReactivatingVirus = false;
	m_virusIsIsolated = false;
	m_virusesBeforeReactivate = -5;
	m_virusesAfterReactivate= -10;

	createCave();

	for (int i = 0; i < 4; i++)
		smoothCave();

	//startSpreadVirus(500.0f, 200.0f);
	startSpreadVirus(50.0f, 20.0f);
}

void World::createCave()
{
	int fillPercent = 48;

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;

			if (x == 0 || x == m_width - 1 || y == 0 || y == m_height - 1)
				m_mapData[index] = TileType::BORDER;
			else if (RandomNumGen::getInstance().generateInteger(0, 100) <= fillPercent)
				m_mapData[index] = TileType::GROUND;
			else
				m_mapData[index] = TileType::EMPTY;
		}
	}
}

void World::smoothCave()
{
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;

			int adjacentCount = getSurroundingCount(x, y, true);

			if (x == 0 || x == m_width - 1 || y == 0 || y == m_height - 1)
				m_mapData[index] = TileType::BORDER;
			else if (adjacentCount > 4)
				m_mapData[index] = TileType::GROUND;
			else if (adjacentCount < 4)
				m_mapData[index] = TileType::EMPTY;
		}
	}
}

int World::getSurroundingCount(int gridX, int gridY, bool wall)
{
	int adjacentCount = 0;
	for (int adjacentX = gridX - 1; adjacentX <= gridX + 1; adjacentX++)
	{
		for (int adjacentY = gridY - 1; adjacentY <= gridY + 1; adjacentY++)
		{
			if (adjacentX >= 0 && adjacentX < m_width && adjacentY >= 0 && adjacentY < m_height)
			{
				if (adjacentX != gridX || adjacentY != gridY)
				{
					int index = adjacentY * m_width + adjacentX;

					if (wall)
					{
						if (m_mapData[index] == TileType::GROUND || m_mapData[index] == TileType::BORDER)
							adjacentCount += 1;
					}
					else
					{
						if (m_mapData[index] == TileType::EMPTY || m_mapData[index] == TileType::GROUND_DESTROYED)
							adjacentCount += 1;
					}
				}
			}
			else
				adjacentCount++;
		}
	}
	return adjacentCount;
}

void World::startSpreadVirus(float tileX, float tileY)
{
	int index = tileY * m_width + tileX;

	//make space for the virus initialization
	createHole(tileX, tileY, 10.0f);

	m_virusIndices.push_back(index);
}

void World::update(float deltaTime)
{
	m_virusSpreadTimer += deltaTime;

	if (!m_virusIsIsolated && m_virusSpreadTimer > 0.5f)
	{
		m_virusSpreadTimer = 0.0f;

		if (m_currentlyReactivatingVirus)
			updateVirusReactivation();
		else
			updateVirus();
	}
}

void World::updateVirus()
{
	int numVirus = m_virusIndices.size();
	int maxUpdates = 40;
	int numUpdates = 0;
	int loopIterations = 0;
	bool anyVirusAdded = false;

	bool indices[8] = { false };

	for (int i = 0; i < 4;)
	{
		int rand = RandomNumGen::getInstance().generateInteger(0, 7);

		if (indices[rand] == false)
		{
			indices[rand] = true;
			i++;
		}
	}

	for (int i = m_currVirusIteration; i < numVirus; i++)
	{
		int indexstuff[8] = {
			m_virusIndices[i] - m_width - 1,
			m_virusIndices[i] - m_width,
			m_virusIndices[i] - m_width + 1,
			m_virusIndices[i] - 1,
			m_virusIndices[i] + 1,
			m_virusIndices[i] + m_width - 1,
			m_virusIndices[i] + m_width,
			m_virusIndices[i] + m_width + 1 };

		for (int j = 0; j < 8; j++)
		{
			if (indices[j] == false)
				continue;

			if (indexstuff[j] < 0 || indexstuff[j] > m_mapData.size() - 1)
				continue;

			if (m_mapData[indexstuff[j]] == TileType::EMPTY || m_mapData[indexstuff[j]] == TileType::GROUND_DESTROYED)
			{
				m_virusIndices.push_back(indexstuff[j]);
				m_mapData[indexstuff[j]] = TileType::VIRUS;
				numUpdates++;
			}
		}

		loopIterations++;

		if (numUpdates > maxUpdates)
		{
			numVirus -= maxUpdates;
			break;
		}
	}

	m_currVirusIteration += loopIterations;

	if (m_virusesBeforeReactivate == m_virusesAfterReactivate && numUpdates == 0)
	{
		m_virusIsIsolated = true;
	}

	if (numUpdates == 0)
	{
		m_currentlyReactivatingVirus = true;
		m_virusesBeforeReactivate = m_virusIndices.size();
		m_virusIndices.clear();
		m_virusIndices.reserve(m_width * m_height);
		m_currVirusIteration = 0;
	}
}

void World::updateVirusReactivation()
{
	int i;
	// reactivate sleeping viruses
	for (i = m_currReactivateVirusIteration; i < m_mapData.size(); i++)
	{
		if (m_mapData[i] == TileType::VIRUS)
		{
			m_virusIndices.push_back(i);
		}

		if (i > m_mapData.size()/4)
			break;
	}

	m_currReactivateVirusIteration += i;

	if (m_currReactivateVirusIteration >= m_mapData.size() - 1)
	{
		m_currReactivateVirusIteration = 0;
		m_virusesAfterReactivate = m_virusIndices.size();
		m_currentlyReactivatingVirus = false;
	}
}

void World::createHole(float tileX, float tileY, float radius)
{
	// bresenham circle
	int x = 0;
	int y = radius;
	int p = 3 - 2 * radius;

	if (!radius) 
		return;

	auto drawline = [&](int sx, int ex, int ny)
	{

		for (int i = sx; i < ex; i++)
		{
			if (ny >= 0 && ny < m_height && i >= 0 && i < m_width)
			{
				int index = ny*m_width + i;

				if (m_mapData[index] == TileType::GROUND)
					m_mapData[index] = TileType::GROUND_DESTROYED;
				else if (m_mapData[index] == TileType::VIRUS)
					m_mapData[index] = TileType::GROUND_DESTROYED;
			}
		}
	};

	while (y >= x)
	{
		drawline(tileX - x, tileX + x, tileY - y);
		drawline(tileX - y, tileX + y, tileY - x);
		drawline(tileX - x, tileX + x, tileY + y);
		drawline(tileX - y, tileX + y, tileY + x);

		if (p < 0)
			p += 4 * x++ + 6;
		else
			p += 4 * (x++ - y--) + 10;
	}
}

void World::createGroundMass(float tileX, float tileY, float radius)
{
	// bresenham circle
	int x = 0;
	int y = radius;
	int p = 3 - 2 * radius;

	if (!radius)
		return;

	auto drawline = [&](int sx, int ex, int ny)
	{

		for (int i = sx; i < ex; i++)
		{
			if (ny >= 0 && ny < m_height && i >= 0 && i < m_width)
			{
				int index = ny*m_width + i;

				if (m_mapData[index] == TileType::EMPTY || m_mapData[index] == TileType::GROUND_DESTROYED || m_mapData[index] == TileType::VIRUS)
					m_mapData[index] = TileType::GROUND;
			}
		}
	};

	while (y >= x)
	{
		drawline(tileX - x, tileX + x, tileY - y);
		drawline(tileX - y, tileX + y, tileY - x);
		drawline(tileX - x, tileX + x, tileY + y);
		drawline(tileX - y, tileX + y, tileY + x);

		if (p < 0)
			p += 4 * x++ + 6;
		else
			p += 4 * (x++ - y--) + 10;
	}
}

void World::draw(sf::RenderWindow& window, sf::View& camera)
{
	sf::VertexArray screenView(sf::Quads);

	int startX = (camera.getCenter().x - camera.getSize().x / 2) / m_tileSize;
	int startY = (camera.getCenter().y - camera.getSize().y / 2) / m_tileSize;

	int endX = (camera.getCenter().x + camera.getSize().x / 2) / m_tileSize + 1;
	int endY = (camera.getCenter().y + camera.getSize().y / 2) / m_tileSize + 1;

	if (startX < 0)
		startX = 0;

	if (startY < 0)
		startY = 0;

	if (endX > m_width)
		endX = m_width;

	if (endY > m_height)
		endY = m_height;

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			int index = y * m_width + x;

			if (m_mapData[index] == TileType::GROUND) //dont draw the ground
				continue;

			sf::Vector2f position1(x* m_tileSize, y * m_tileSize);
			sf::Vector2f position2((x* m_tileSize) + m_tileSize, y * m_tileSize);
			sf::Vector2f position3((x* m_tileSize) + m_tileSize, (y * m_tileSize) + m_tileSize);
			sf::Vector2f position4(x* m_tileSize, (y * m_tileSize) + m_tileSize);

			if (m_mapData[index] == TileType::GROUND_DESTROYED)
			{
				sf::Color grey(220, 220, 220);

				screenView.append(sf::Vertex(position1, grey));
				screenView.append(sf::Vertex(position2, grey));
				screenView.append(sf::Vertex(position3, grey));
				screenView.append(sf::Vertex(position4, grey));
			}
			else if (m_mapData[index] == TileType::EMPTY)
			{
				screenView.append(sf::Vertex(position1, sf::Color::White));
				screenView.append(sf::Vertex(position2, sf::Color::White));
				screenView.append(sf::Vertex(position3, sf::Color::White));
				screenView.append(sf::Vertex(position4, sf::Color::White));
			}
			else if (m_mapData[index] == TileType::BORDER)
			{
				if (x == 0 || x == m_width - 1)
				{
					// left and right border
					screenView.append(sf::Vertex(position1, sf::Color::Black));
					screenView.append(sf::Vertex(position2, sf::Color::White));
					screenView.append(sf::Vertex(position3, sf::Color::White));
					screenView.append(sf::Vertex(position4, sf::Color::Black));
				}
				else
				{
					// top and bottom border
					screenView.append(sf::Vertex(position1, sf::Color::Black));
					screenView.append(sf::Vertex(position2, sf::Color::Black));
					screenView.append(sf::Vertex(position3, sf::Color::White));
					screenView.append(sf::Vertex(position4, sf::Color::White));
				}
			}
			else if (m_mapData[index] == TileType::VIRUS)
			{
				screenView.append(sf::Vertex(position1, sf::Color::Green));
				screenView.append(sf::Vertex(position2, sf::Color::Green));
				screenView.append(sf::Vertex(position3, sf::Color::Green));
				screenView.append(sf::Vertex(position4, sf::Color::Green));
			}
		}
	}

	window.draw(screenView);
}

std::vector<char>& World::getMapData()
{
	return m_mapData;
}