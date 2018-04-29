#include "InputComponent.h"

#include "../objects/Entity.h"

#include <SFML\Window\Keyboard.hpp>
#include <SFML\System\Vector2.hpp>

InputComponent::InputComponent(luabridge::LuaRef& componentTable)
{
	
}

void InputComponent::update(Entity& entity, float deltaTime)
{
	static const float MOVE_ACCELERATION = 5.0f;
	sf::Vector2f newPos(entity.getFloat("x"), entity.getFloat("y"));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		newPos.x -= MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		newPos.x += MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		newPos.y -= MOVE_ACCELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		newPos.y += MOVE_ACCELERATION;

	entity.addFloat("x", newPos.x);
	entity.addFloat("y", newPos.y);
}