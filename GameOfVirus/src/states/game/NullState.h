#pragma once

#include "IGameState.h"

class NullState : public IGameState
{
public:
	virtual void init(StateMachine& stateMachine, sf::RenderWindow& window) override
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