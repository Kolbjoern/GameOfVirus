#pragma once

#include "FPSCounter.h"

#include <SFML\Graphics\RenderWindow.hpp>

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void init();
	void handleInput();
	void update(float deltaTime);
	void render();

	FPSCounter m_fpsCounter;

	sf::RenderWindow m_window;
};

