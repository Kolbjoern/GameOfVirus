#include "InputComponent.h"

#include <SFML\Window\Keyboard.hpp>

InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::update(Entity& entity, float deltaTime)
{
	static const float MOVE_ACCELERATION = 5.0f;
	sf::Vector2f newAcceleration(entity.getAcceleration());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		newAcceleration.x -= MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		newAcceleration.x += MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		newAcceleration.y -= MOVE_ACCELERATION*2;

	entity.setAcceleration(newAcceleration);
}