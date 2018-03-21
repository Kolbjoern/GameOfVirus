#include "Gunslinger.h"

#include "../components/ControllerComponent.h"
#include "../components/PhysicsComponent.h"
#include "../utils/VectorMath.h"
#include "../utils/RandomNumGen.h"

#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Keyboard.hpp>

Gunslinger::Gunslinger()
{
}

Gunslinger::~Gunslinger()
{
}

void Gunslinger::init(float radius, sf::Vector2f position)
{
	m_entity.init(radius, sf::Color::Red, new PlayerControllerComponent(), new ActorPhysicsComponent());
	m_entity.setPosition(position);
	m_currentGun = 0;
	m_reloadTimer = 0.0f;
}

void Gunslinger::update(World& world, sf::RenderWindow& window, sf::View& camera, std::vector<Gun>& guns, std::vector<Entity>& projectiles, float deltaTime)
{
	m_entity.update(world, window, camera, deltaTime);
	
	m_reloadTimer += deltaTime;

	if (!window.hasFocus())
		return;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && guns.size() >= 0))
		m_currentGun = 0;

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)))
	{
		sf::Vector2i windowPos = sf::Mouse::getPosition(window);
		sf::Vector2f mouseDir = sf::Vector2f((windowPos.x + camera.getCenter().x - camera.getSize().x / 2), (windowPos.y + camera.getCenter().y - camera.getSize().y / 2));
		sf::Vector2f centerDir = m_entity.getPosition() + sf::Vector2f(m_entity.getRadius(), m_entity.getRadius());

		sf::Vector2f direction = mouseDir - centerDir;
		sf::Vector2f normalized = VectorMath::normalize(direction);

		if (m_currentGun != -1 && guns.size() > 0 && m_currentGun < guns.size())
		{
			guns[m_currentGun].update(centerDir, normalized, projectiles, m_reloadTimer);
		}
	}
}

void Gunslinger::draw(sf::RenderWindow& window)
{
	m_entity.draw(window);
}

sf::Vector2f Gunslinger::getPosition()
{
	return m_entity.getPosition();
}

const int Gunslinger::getCurrentGunIndex()
{
	return m_currentGun;
}