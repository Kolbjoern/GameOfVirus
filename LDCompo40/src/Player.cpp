#include "Player.h"

#include <SFML\Window\Keyboard.hpp>

#include "Globals.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float radius)
{
	m_body.setRadius(radius);
	m_body.setFillColor(sf::Color::Red);
	m_body.setPosition(120.0f, 100.0f);
}

void Player::update(std::vector<char>& map, sf::View& camera, float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_acceleration.x -= 5.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_acceleration.x += 5.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_acceleration.y -= 5.0f;
	else
		m_acceleration.y += 5.0f;

	m_velocity += m_acceleration * deltaTime;

	sf::Vector2f nextPos = m_body.getPosition() + m_velocity;
		
	m_acceleration.x = 0.0f;
	m_acceleration.y = 0.0f;

	float angle = atan2f(m_velocity.y, m_velocity.x);
	sf::Vector2f response(0.0f, 0.0f);
	bool collision = false;
	const float PI = 3.14159f;

	for (float r = angle - PI / 2.0f; r < angle + PI; r += PI / 8.0f)
	{
		sf::Vector2f testPosition(
			m_body.getRadius() * cosf(r) + nextPos.x,
			m_body.getRadius() * sinf(r) + nextPos.y);
			
		testPosition += sf::Vector2f(m_body.getRadius(), m_body.getRadius());

		if (testPosition.x >= WORLD_WIDTH*TILE_SIZE)
			testPosition.x = WORLD_WIDTH*TILE_SIZE - 1;

		if (testPosition.y >= WORLD_HEIGHT*TILE_SIZE)
			testPosition.y = WORLD_HEIGHT*TILE_SIZE - 1;

		if (testPosition.x < 0)
			testPosition.x = 0;

		if (testPosition.y < 0)
			testPosition.y = 0;

		int index = (int)testPosition.y/TILE_SIZE * WORLD_WIDTH + (int)testPosition.x/TILE_SIZE;

		if (map[index] != 0)
		{
			response += (nextPos + sf::Vector2f(m_body.getRadius(), m_body.getRadius())) - testPosition;
			collision = true;
		}
	}

	float magResponse = sqrtf(response.x * response.x + response.y * response.y);
	float friction = 0.8f;

	if (collision)
	{
		float dot = m_velocity.x * (response.x / magResponse) +
			m_velocity.y * (response.y / magResponse);

		m_velocity = sf::Vector2f(friction * (-2.0f * dot * (response.x / magResponse) + m_velocity.x),
								  friction * (-2.0f * dot * (response.y / magResponse) + m_velocity.y));
	}
	else
		m_body.setPosition(nextPos);

	// slow down
	m_velocity.x *= 0.98f;
	m_velocity.y *= 0.98f;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

void Player::setPosition(sf::Vector2f newPosition)
{
	m_body.setPosition(newPosition);
}

sf::Vector2f Player::getPosition()
{
	return m_body.getPosition();
}