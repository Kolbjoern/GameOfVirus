#include "PhysicsComponent.h"

#include "../Globals.h"

void ActorPhysicsComponent::update(Entity& entity, World& world, float deltaTime)
{
	if (!entity.getIsBullet())
	{
		static const float GRAVITY = 5.0f;
		entity.setAcceleration(sf::Vector2f(entity.getAcceleration().x, entity.getAcceleration().y + GRAVITY));
	}

	entity.setVelocity(entity.getVelocity() + entity.getAcceleration() * deltaTime);

	sf::Vector2f nextPos = entity.getPosition() + entity.getVelocity();

	entity.setAcceleration(sf::Vector2f(0.0f, 0.0f));

	float angle = atan2f(entity.getVelocity().y, entity.getVelocity().x);
	sf::Vector2f response(0.0f, 0.0f);
	bool collision = false;
	const float PI = 3.14159f;

	for (float r = angle - PI / 2.0f; r < angle + PI; r += PI / 8.0f)
	{
		sf::Vector2f testPosition(
			entity.getRadius() * cosf(r) + nextPos.x,
			entity.getRadius() * sinf(r) + nextPos.y);

		testPosition += sf::Vector2f(entity.getRadius(), entity.getRadius());

		if (testPosition.x >= WORLD_WIDTH*TILE_SIZE)
			testPosition.x = WORLD_WIDTH*TILE_SIZE - 1;

		if (testPosition.y >= WORLD_HEIGHT*TILE_SIZE)
			testPosition.y = WORLD_HEIGHT*TILE_SIZE - 1;

		if (testPosition.x < 0)
			testPosition.x = 0;

		if (testPosition.y < 0)
			testPosition.y = 0;

		int index = (int)testPosition.y / TILE_SIZE * WORLD_WIDTH + (int)testPosition.x / TILE_SIZE;

		if (world.getMapData()[index] != TileType::EMPTY && world.getMapData()[index] != TileType::GROUND_DESTROYED)
		{
			response += (nextPos + sf::Vector2f(entity.getRadius(), entity.getRadius())) - testPosition;
			collision = true;
		}
	}

	float magResponse = sqrtf(response.x * response.x + response.y * response.y);
	float friction = 0.9f;

	if (collision)
	{
		float dot = entity.getVelocity().x * (response.x / magResponse) +
			entity.getVelocity().y * (response.y / magResponse);

		if (entity.getIsBullet())
		{
			world.createHole(nextPos.x / TILE_SIZE, nextPos.y / TILE_SIZE, 3.0f);
			entity.setIsDead(true);
		}
		else if (entity.getIsMass())
		{
			world.createGroundMass(nextPos.x / TILE_SIZE, nextPos.y / TILE_SIZE, 5.0f);
			entity.setIsDead(true);
		}
		else
		{
			entity.setVelocity(sf::Vector2f(friction * (-2.0f * dot * (response.x / magResponse) + entity.getVelocity().x),
											friction * (-2.0f * dot * (response.y / magResponse) + entity.getVelocity().y)));
		}
	}
	else
		entity.setPosition(nextPos);

	// slow down
	if (!entity.getIsBullet() && !entity.getIsMass())
		entity.setVelocity(entity.getVelocity() * 0.98f);
}