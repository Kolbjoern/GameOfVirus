#pragma once

#include "Gun.h"

class Gunslinger
{
public:
	Gunslinger();
	~Gunslinger();

	void init(float radius, sf::Vector2f position);
	void update(World& world, sf::RenderWindow& window, sf::View& camera, std::vector<Gun>& guns, std::vector<Entity>& projectiles, float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition();

private:
	Entity m_entity;

	int m_currentGun;
	float m_reloadTimer;
};

