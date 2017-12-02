#include "Entity.h"

#include "../World.h"
#include "../Globals.h"
#include "../components\InputComponent.h"
#include "../components\PhysicsComponent.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::init(float radius, sf::Color color, InputComponent* inputComponent, PhysicsComponent* physicsComponent)
{
	m_body.setRadius(radius);
	m_body.setFillColor(color);
	m_isBullet = false;
	m_isDead = false;

	m_inputComponent = inputComponent;
	m_physicsComponent = physicsComponent;
}

void Entity::update(World& world, sf::RenderWindow& window, sf::View& camera, float deltaTime)
{
	if (m_inputComponent != nullptr)
		m_inputComponent->update(*this, deltaTime);

	if (m_physicsComponent != nullptr)
		m_physicsComponent->update(*this, world, deltaTime);
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

void Entity::setPosition(sf::Vector2f newPosition)
{
	m_body.setPosition(newPosition);
}

void Entity::setAcceleration(sf::Vector2f newAcceleration)
{
	m_acceleration = newAcceleration;
}

void Entity::setVelocity(sf::Vector2f newVelocity)
{
	m_velocity = newVelocity;
}

void Entity::setIsBullet(bool value)
{
	m_isBullet = value;
}

void Entity::setIsDead(bool value)
{
	m_isDead = value;
}

sf::Vector2f Entity::getPosition()
{
	return m_body.getPosition();
}

sf::Vector2f Entity::getAcceleration()
{
	return m_acceleration;
}

sf::Vector2f Entity::getVelocity()
{
	return m_velocity;
}

bool Entity::getIsBullet()
{
	return m_isBullet;
}

bool Entity::getIsDead()
{
	return m_isDead;
}

float Entity::getRadius()
{
	return m_body.getRadius();
}