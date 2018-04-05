#pragma once

#include <SFML\Graphics\RenderWindow.hpp>

// forward declarations
class StateMachine;

class IGameState
{
public:
	virtual void init(StateMachine& stateMachine, sf::RenderWindow& window) = 0;
	virtual void handleInput() = 0;
	virtual void update(float feltaTime) = 0;
	virtual void render() = 0;
	virtual void exit() = 0;
};

