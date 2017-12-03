#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\VertexArray.hpp>

class World
{
public:
	World();
	~World();

	enum TileType
	{
		EMPTY = 0,
		GROUND = 1,
		BORDER = 2,
		GROUND_DESTROYED = 3,
		VIRUS = 4
	};

	void init(int tileSize, int width, int height);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window, sf::View& camera);

	void createHole(float tileX, float tileY, float radius);
	void createGroundMass(float tileX, float tileY, float radius);

	std::vector<char>& getMapData();

private:
	void createCave();
	void smoothCave();
	int getSurroundingCount(int gridX, int gridY, bool wall);
	void startSpreadVirus(float tileX, float tileY);

	std::vector<char> m_mapData;
	int m_tileSize;
	int m_width;
	int m_height;
	float m_virusSpreadTimer;
	int m_currVirusIteration;

	std::vector<int> m_virusIndices;
};

