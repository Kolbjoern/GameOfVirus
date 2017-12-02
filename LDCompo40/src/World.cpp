#include "World.h"

#include <random>

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

	createCave();

	for (int i = 0; i < 4; i++)
		smoothCave();
}

void World::createCave()
{
	std::mt19937 randomGenerator;
	int seed = 1337;//time(nullptr);
	randomGenerator.seed(seed);
	std::uniform_int_distribution<int> randomFillPercent(0, 100);

	int fillPercent = 48;

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			int index = y * m_width + x;

			if (x == 0 || x == m_width - 1 || y == 0 || y == m_height - 1)
				m_mapData[index] = TileType::BORDER;
			else if (randomFillPercent(randomGenerator) <= fillPercent)
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

			int neighborCount = getSurroundingWallCount(x, y);

			if (x == 0 || x == m_width - 1 || y == 0 || y == m_height - 1)
				m_mapData[index] = TileType::BORDER;
			else if (neighborCount > 4)
				m_mapData[index] = TileType::GROUND;
			else if (neighborCount < 4)
				m_mapData[index] = TileType::EMPTY;
		}
	}
}

int World::getSurroundingWallCount(int gridX, int gridY)
{
	int wallCount = 0;
	for (int neighborX = gridX - 1; neighborX <= gridX + 1; neighborX++)
	{
		for (int neighborY = gridY - 1; neighborY <= gridY + 1; neighborY++)
		{
			if (neighborX >= 0 && neighborX < m_width && neighborY >= 0 && neighborY < m_height)
			{
				if (neighborX != gridX || neighborY != gridY)
				{
					int index = neighborY * m_width + neighborX;

					if (m_mapData[index] == TileType::GROUND || m_mapData[index] == TileType::BORDER)
						wallCount += 1;
				}
			}
			else
				wallCount++;
		}
	}
	return wallCount;
}

void World::createHole(float worldX, float worldY, float radius)
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
				if (m_mapData[ny*m_width + i] == TileType::GROUND)
					m_mapData[ny*m_width + i] = TileType::GROUND_DESTROYED;
			}
		}
	};

	while (y >= x)
	{
		drawline(worldX - x, worldX + x, worldY - y);
		drawline(worldX - y, worldX + y, worldY - x);
		drawline(worldX - x, worldX + x, worldY + y);
		drawline(worldX - y, worldX + y, worldY + x);

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
		}
	}

	window.draw(screenView);
}

std::vector<char>& World::getMapData()
{
	return m_mapData;
}