#pragma once

#include "../World.h"

#include <vector>

class Virus
{
public:
	Virus();
	~Virus();

	void init(int tileX, int tileY, World* world);
	void update(float deltaTime);

	void startSpreading();

	bool getIsIsolated();
	bool getIsDestroyed();

private:
	void updateGrowth();
	void reactivateSleepers();
	bool checkIfDead();

	World* m_world;

	sf::Vector2f m_initPoint;

	std::vector<int> m_infectedTileIndices;

	float m_spreadTimer;
	int m_currentIteration;
	int m_currentReactivateIteration;
	bool m_currentlyReactivating;
	bool m_isIsolated;
	bool m_isDestroyed;
	int m_numBeforeReactivate;
	int m_numAfterReactivate;
};

