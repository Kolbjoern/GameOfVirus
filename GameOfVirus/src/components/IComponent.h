#pragma once

class Object;

class IComponent
{
public:
	virtual void update(Object& object, float deltaTime) {};// = 0;
};