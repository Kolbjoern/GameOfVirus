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
		BORDER = 2
	};

	void init(int tileSize, int width, int height);
	void draw(sf::RenderWindow& window, sf::View& camera);

	void createHole(float worldX, float worldY, float radius);

	std::vector<char>& getData();

private:
	void createCave();
	void smoothCave();
	int getSurroundingWallCount(int gridX, int gridY);

	std::vector<char> m_data;
	int m_tileSize;
	int m_width;
	int m_height;
};

