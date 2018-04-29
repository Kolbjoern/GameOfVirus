#pragma once

#include "../EntityOLD.h"

class ControllerComponent
{
public:
	virtual void update(EntityOLD& entity, float deltaTime) = 0;
};

class PlayerControllerComponent : public ControllerComponent
{
	virtual void update(EntityOLD& entity, float deltaTime);
};