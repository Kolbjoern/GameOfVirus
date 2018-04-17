#include "InputComponent.h"

#include "../objects/Object.h"

#include <SFML\Window\Keyboard.hpp>
#include <SFML\System\Vector2.hpp>

void InputComponent::update(Object& object, float deltaTime)
{
	static const float MOVE_ACCELERATION = 5.0f;
	sf::Vector2f newPos(object.getFloat("x"), object.getFloat("y"));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		newPos.x -= MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		newPos.x += MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		newPos.y -= MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		newPos.y += MOVE_ACCELERATION;

	object.addFloat("x", newPos.x);
	object.addFloat("y", newPos.y);
}