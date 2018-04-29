#pragma once

#include "utils/FPSCounter.h"
#include "World.h"
#include "EntityOLD.h"
#include "objects/Virus.h"
#include "objects\Gunslinger.h"
#include "TileShape.h"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

class GameOLD
{
public:
	GameOLD();
	~GameOLD();

	void run();

private:
	void init();
	void handleInput();
	void update(float deltaTime);
	void render();

	FPSCounter m_fpsCounter;
	World m_world;
	Virus m_virus;
	Gunslinger m_player;
	std::vector<Gun> m_guns;

	std::vector<EntityOLD> m_projectiles;
	std::vector<EntityOLD> m_debris;

	sf::RenderWindow m_window;
	sf::View m_camera;
	sf::Font m_font;
	sf::Text m_infoText;
	std::vector<sf::Text> m_wepTxt;

	bool m_done;
};

