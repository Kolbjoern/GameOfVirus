#pragma once

#include "../World.h"
#include "../EntityOLD.h"

class Gun
{
public:
	void init(std::string name, float radius, float fireRate, int numProjectiles, float spread, float speed, float bulletLifeTime);
	void update(sf::Vector2f position, sf::Vector2f direction, std::vector<EntityOLD>& projectiles, float& reloadTimer);

	const std::string getName();

private:
	std::string m_name;
	float m_radius;
	float m_fireRate;
	int m_numProjectiles;
	float m_spread;
	float m_speed;
	float m_bulletLifeTime;
};

