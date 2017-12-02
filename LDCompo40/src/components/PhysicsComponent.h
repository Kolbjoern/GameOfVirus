#pragma once

#include "../World.h"
#include "../objects/Entity.h"

class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	void update(Entity& entity, World& world, float deltaTime);
};

