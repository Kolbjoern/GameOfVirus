#include "Gun.h"

#include "../utils/RandomNumGen.h"
#include "../utils/VectorMath.h"
#include "../components/PhysicsComponent.h"

#include <SFML\Window\Mouse.hpp>

void Gun::init(std::string name, float radius, float fireRate, int numProjectiles, float spread, float speed, float bulletLifeTime)
{
	m_name = name;
	m_radius = radius;
	m_fireRate = fireRate;
	m_numProjectiles = numProjectiles;
	m_spread = spread;
	m_speed = speed;
	m_bulletLifeTime = bulletLifeTime;
}

void Gun::update(sf::Vector2f position, sf::Vector2f direction, std::vector<Entity>& projectiles, float& reloadTimer)
{
	if (reloadTimer > m_fireRate)
	{
		reloadTimer = 0.0f;

		const float DEG_TO_RAND = 3.14159265359f / 180.0f;

		for (int i = 0; i < m_numProjectiles; i++)
		{
			Entity p;
			p.setPosition(position - sf::Vector2f(m_radius, m_radius));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				p.init(m_radius, sf::Color::Magenta, nullptr, new ActorPhysicsComponent());
				p.setAcceleration(m_speed * VectorMath::rotate(direction, RandomNumGen::getInstance().generateFloat(-DEG_TO_RAND * m_spread, DEG_TO_RAND * m_spread)));
				p.setIsBullet(true);
				p.setLifeTime(m_bulletLifeTime);
			}
			else
			{
				p.init(m_radius, sf::Color::Black, nullptr, new ActorPhysicsComponent());
				p.setAcceleration(m_speed * VectorMath::rotate(direction, RandomNumGen::getInstance().generateFloat(-DEG_TO_RAND * m_spread, DEG_TO_RAND * m_spread)));
				p.setIsMass(true);
				p.setLifeTime(m_bulletLifeTime);
			}
			projectiles.emplace_back(p);
		}
	}
}
