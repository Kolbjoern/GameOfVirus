#pragma once

#include "../objects/Entity.h"

class InputComponent
{
public:
	InputComponent();
	~InputComponent();

	void update(Entity& entity, float deltaTime);
};

