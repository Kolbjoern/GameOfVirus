#pragma once

#include <SFML\Graphics\RenderWindow.hpp>

class IGameState
{
public:
	virtual void init(sf::RenderWindow& window) = 0;
	virtual void handleInput() = 0;
	virtual void update(float feltaTime) = 0;
	virtual void render() = 0;
	virtual void exit() = 0;
};

