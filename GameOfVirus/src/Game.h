#pragma once

#include "managers\StateMachine.h"
#include "states\game\MenuState.h"
#include "states\game\WorldState.h"
#include "utils\LoopTimer.h"

#include <SFML\Graphics\RenderWindow.hpp>

class Game
{
public:
	void run();

private:
	void init();

	StateMachine m_stateMachine;
	MenuState m_menu;
	WorldState m_world;
	LoopTimer m_loopTimer;

	sf::RenderWindow m_window;
};

