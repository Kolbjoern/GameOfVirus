#pragma once

#include "../World.h"
#include "../EntityOLD.h"

class PhysicsComponent
{
public:
	virtual void update(EntityOLD& entity, World& world, float deltaTime) = 0;
};

class ActorPhysicsComponent : public PhysicsComponent
{
	virtual void update(EntityOLD& entity, World& world, float deltaTime);
};

