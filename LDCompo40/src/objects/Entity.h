#pragma once

#include "../World.h"

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

// forward declarations
class InputComponent;
class PhysicsComponent;

class Entity
{
public:
	Entity();
	~Entity();

	void init(float radius, sf::Color color, InputComponent* inputComponent, PhysicsComponent* physicsComponent);
	void update(World& world, sf::RenderWindow& window, sf::View& camera, float deltaTime);
	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f newPosition);
	void setAcceleration(sf::Vector2f newAcceleration);
	void setVelocity(sf::Vector2f newVelocity);
	void setIsBullet(bool value);
	void setIsDead(bool value);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getAcceleration();
	float getRadius();
	bool getIsBullet();
	bool getIsDead();

private:
	InputComponent* m_inputComponent;
	PhysicsComponent* m_physicsComponent;

	sf::CircleShape m_body;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	bool m_isBullet;
	bool m_isDead;
};