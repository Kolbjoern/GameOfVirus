#include "Virus.h"

#include "../Globals.h"
#include "../utils/RandomNumGen.h"

Virus::Virus()
{
}

Virus::~Virus()
{
}

void Virus::init(int tileX, int tileY, World* world)
{
	m_initPoint.x = tileX;
	m_initPoint.y = tileY;
	m_world = world;

	m_infectedTileIndices.reserve(WORLD_WIDTH * WORLD_HEIGHT);

	m_spreadTimer = 0.0f;
	m_currentIteration = 0;
	m_currentReactivateIteration = 0;
	m_currentlyReactivating = false;
	m_isIsolated = false;
	m_isDestroyed = false;
	m_numBeforeReactivate = -1;
	m_numAfterReactivate = -2;
}

void Virus::update(float deltaTime)
{
	m_spreadTimer += deltaTime;

	if (!m_isDestroyed && m_spreadTimer > 0.5f)
	{
		if (!m_isIsolated)
		{
			m_spreadTimer = 0.0f;

			if (m_currentlyReactivating)
				reactivateSleepers();
			else
				updateGrowth();
		}
		else
		{
			if (checkIfDead())
				m_isDestroyed = true;
		}
	}
}

void Virus::startSpreading()
{
	int index = m_initPoint.y * WORLD_WIDTH + m_initPoint.x;

	//make space for the virus initialization
	m_world->createHole(m_initPoint.x, m_initPoint.y, 10);

	m_infectedTileIndices.push_back(index);
}

void Virus::updateGrowth()
{
	int numVirus = m_infectedTileIndices.size();
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

	for (int i = m_currentIteration; i < numVirus; i++)
	{
		int indexstuff[8] = {
			m_infectedTileIndices[i] - WORLD_WIDTH - 1,
			m_infectedTileIndices[i] - WORLD_WIDTH,
			m_infectedTileIndices[i] - WORLD_WIDTH + 1,
			m_infectedTileIndices[i] - 1,
			m_infectedTileIndices[i] + 1,
			m_infectedTileIndices[i] + WORLD_WIDTH - 1,
			m_infectedTileIndices[i] + WORLD_WIDTH,
			m_infectedTileIndices[i] + WORLD_WIDTH + 1 };

		for (int j = 0; j < 8; j++)
		{
			if (indices[j] == false)
				continue;

			if (indexstuff[j] < 0 || indexstuff[j] > m_world->getMapData().size() - 1)
				continue;

			if (m_world->getMapData()[indexstuff[j]] == TileType::EMPTY || m_world->getMapData()[indexstuff[j]] == TileType::GROUND_DESTROYED)
			{
				m_infectedTileIndices.push_back(indexstuff[j]);
				m_world->getMapData()[indexstuff[j]] = TileType::VIRUS;
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

	m_currentIteration += loopIterations;

	if (m_numBeforeReactivate == m_numAfterReactivate && numUpdates == 0)
	{
		m_isIsolated = true;
	}

	if (numUpdates == 0)
	{
		m_currentlyReactivating = true;
		m_numBeforeReactivate = m_infectedTileIndices.size();
		m_infectedTileIndices.clear();
		m_infectedTileIndices.reserve(WORLD_WIDTH * WORLD_HEIGHT);
		m_currentIteration = 0;
	}
}

void Virus::reactivateSleepers()
{
	int i;
	// reactivate sleeping viruses
	for (i = m_currentReactivateIteration; i < m_world->getMapData().size(); i++)
	{
		if (m_world->getMapData()[i] == TileType::VIRUS)
		{
			m_infectedTileIndices.push_back(i);
		}

		if (i > m_world->getMapData().size() / 4)
			break;
	}

	m_currentReactivateIteration += i;

	if (m_currentReactivateIteration >= m_world->getMapData().size() - 1)
	{
		m_currentReactivateIteration = 0;
		m_numAfterReactivate = m_infectedTileIndices.size();
		m_currentlyReactivating = false;
	}
}

bool Virus::checkIfDead()
{
	// reactivate sleeping viruses
	for (int i = 0; i < m_world->getMapData().size(); i++)
	{
		if (m_world->getMapData()[i] == TileType::VIRUS)
			return false;
	}

	return true;
}

bool Virus::getIsIsolated()
{
	return m_isIsolated;
}

bool Virus::getIsDestroyed()
{
	return m_isDestroyed;
}