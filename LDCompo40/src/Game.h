#pragma once

#include "FPSCounter.h"
#include "World.h"
#include "Entity.h"
#include "objects\Gunslinger.h"

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
	Gunslinger m_player;
	std::vector<Gun> m_guns;

	std::vector<Entity> m_projectiles;
	std::vector<Entity> m_debris;

	sf::RenderWindow m_window;
	sf::View m_camera;
};

