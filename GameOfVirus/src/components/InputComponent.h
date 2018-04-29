#pragma once

#include "Component.h"

class Entity;

class InputComponent : public Component
{
public:
	InputComponent(luabridge::LuaRef& componentTable);
	void update(Entity& entity, float dealtTime);
};