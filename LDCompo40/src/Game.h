#pragma once

#include "FPSCounter.h"
#include "World.h"
#include "objects\Entity.h"

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
	World m_world;
	Entity m_player;
	std::vector<Entity> m_projectiles;

	sf::RenderWindow m_window;
	sf::View m_camera;
};

