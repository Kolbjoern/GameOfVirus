#pragma once

#include "../Entity.h"

class ControllerComponent
{
public:
	virtual void update(Entity& entity, float deltaTime) = 0;
};

class PlayerControllerComponent : public ControllerComponent
{
	virtual void update(Entity& entity, float deltaTime);
};