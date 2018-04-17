#pragma once

#include "IComponent.h"

class InputComponent : public IComponent
{
public:
	virtual void update(Object& object, float dealtTime) override;
};