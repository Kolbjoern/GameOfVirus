#pragma once

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class Player
{
public:
	Player();
	~Player();

	void init(float radius);
	void update(std::vector<char>& map, sf::View& camera, float deltaTime);
	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getPosition();

private:
	sf::CircleShape m_body;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
};