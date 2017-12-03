#pragma once

#include "../World.h"
#include "../Entity.h"

class PhysicsComponent
{
public:
	virtual void update(Entity& entity, World& world, float deltaTime) = 0;
};

class ActorPhysicsComponent : public PhysicsComponent
{
	virtual void update(Entity& entity, World& world, float deltaTime);
};

