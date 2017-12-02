#pragma once

#include "FPSCounter.h"
#include "Player.h"
#include "World.h"

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
	Player m_player;
	World m_world;

	sf::RenderWindow m_window;
	sf::View m_camera;
};

