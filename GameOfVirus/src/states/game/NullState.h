#pragma once

#include "IState.h"

class NullState : public IState
{
public:
	virtual void init(sf::RenderWindow& window) override
	{

	}

	virtual void handleInput() override
	{

	}

	virtual void update(float feltaTime) override
	{

	}

	virtual void render() override
	{

	}

	virtual void exit() override
	{

	}
};