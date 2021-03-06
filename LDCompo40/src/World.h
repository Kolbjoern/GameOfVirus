#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\VertexArray.hpp>

enum class TileType
{
	EMPTY = 0,
	GROUND = 1,
	BORDER = 2,
	GROUND_DESTROYED = 3,
	VIRUS = 4,
	VIRUS_UNIT = 5
};

class World
{
public:
	World();
	~World();

	void init(int tileSize, int width, int height);
	void draw(sf::RenderWindow& window, sf::View& camera);

	void createHole(int tileX, int tileY, int radius);
	void createGroundMass(int tileX, int tileY, int radius);

	std::vector<TileType>& getMapData();

private:
	void createCave();
	void smoothCave();
	int getSurroundingCount(int gridX, int gridY, bool wall);

	std::vector<TileType> m_mapData;
	int m_tileSize;
	int m_width;
	int m_height;
};

