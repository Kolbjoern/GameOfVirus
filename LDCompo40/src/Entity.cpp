#include "Entity.h"

#include "World.h"
#include "Globals.h"
#include "components\ControllerComponent.h"
#include "components\PhysicsComponent.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::init(float radius, sf::Color color, ControllerComponent* controllerComponent, PhysicsComponent* physicsComponent)
{
	m_body.setRadius(radius);
	m_body.setFillColor(color);
	m_isBullet = false;
	m_isDead = false;
	m_isMass = false;
	m_lifeTime = -1.0f;

	m_controllerComponent = controllerComponent;
	m_physicsComponent = physicsComponent;
}

void Entity::update(World& world, sf::RenderWindow& window, sf::View& camera, float deltaTime)
{
	if (m_lifeTime != -1.0f)
	{
		m_timeLived += deltaTime;

		if (m_timeLived > m_lifeTime)
			m_isDead = true;
	}

	if (m_isDead)
		return;

	if (m_controllerComponent != nullptr)
		m_controllerComponent->update(*this, deltaTime);

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

void Entity::setIsMass(bool value)
{
	m_isMass = value;
}

void Entity::setIsDead(bool value)
{
	m_isDead = value;
}

void Entity::setLifeTime(float time)
{
	m_lifeTime = time;
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

bool Entity::getIsMass()
{
	return m_isMass;
}

bool Entity::getIsDead()
{
	return m_isDead;
}

float Entity::getRadius()
{
	return m_body.getRadius();
}

float Entity::getLifeTime()
{
	return m_lifeTime;
}