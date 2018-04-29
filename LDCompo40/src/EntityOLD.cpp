#include "EntityOLD.h"

#include "World.h"
#include "Globals.h"
#include "components\ControllerComponent.h"
#include "components\PhysicsComponent.h"

EntityOLD::EntityOLD()
{
}

EntityOLD::~EntityOLD()
{
}

void EntityOLD::init(float radius, sf::Color color, ControllerComponent* controllerComponent, PhysicsComponent* physicsComponent)
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

void EntityOLD::update(World& world, sf::RenderWindow& window, sf::View& camera, float deltaTime)
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

void EntityOLD::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

void EntityOLD::setPosition(sf::Vector2f newPosition)
{
	m_body.setPosition(newPosition);
}

void EntityOLD::setAcceleration(sf::Vector2f newAcceleration)
{
	m_acceleration = newAcceleration;
}

void EntityOLD::setVelocity(sf::Vector2f newVelocity)
{
	m_velocity = newVelocity;
}

void EntityOLD::setIsBullet(bool value)
{
	m_isBullet = value;
}

void EntityOLD::setIsMass(bool value)
{
	m_isMass = value;
}

void EntityOLD::setIsDead(bool value)
{
	m_isDead = value;
}

void EntityOLD::setLifeTime(float time)
{
	m_lifeTime = time;
}

sf::Vector2f EntityOLD::getPosition()
{
	return m_body.getPosition();
}

sf::Vector2f EntityOLD::getAcceleration()
{
	return m_acceleration;
}

sf::Vector2f EntityOLD::getVelocity()
{
	return m_velocity;
}

bool EntityOLD::getIsBullet()
{
	return m_isBullet;
}

bool EntityOLD::getIsMass()
{
	return m_isMass;
}

bool EntityOLD::getIsDead()
{
	return m_isDead;
}

float EntityOLD::getRadius()
{
	return m_body.getRadius();
}

float EntityOLD::getLifeTime()
{
	return m_lifeTime;
}