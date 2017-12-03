#pragma once

#include "World.h"

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

// forward declarations
class ControllerComponent;
class PhysicsComponent;

class Entity
{
public:
	Entity();
	~Entity();

	void init(float radius, sf::Color color, ControllerComponent* controllerComponent, PhysicsComponent* physicsComponent);
	void update(World& world, sf::RenderWindow& window, sf::View& camera, float deltaTime);
	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f newPosition);
	void setAcceleration(sf::Vector2f newAcceleration);
	void setVelocity(sf::Vector2f newVelocity);
	void setIsBullet(bool value);
	void setIsMass(bool value);
	void setIsDead(bool value);
	void setLifeTime(float time);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getAcceleration();
	
	float getRadius();
	float getLifeTime();

	bool getIsBullet();
	bool getIsMass();
	bool getIsDead();

private:
	ControllerComponent* m_controllerComponent;
	PhysicsComponent* m_physicsComponent;

	sf::CircleShape m_body;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	float m_lifeTime;
	float m_timeLived;

	bool m_isBullet;
	bool m_isMass;
	bool m_isDead;
};