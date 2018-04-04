#include "Game.h"

#include <SFML\Window\Event.hpp>

void Game::run()
{
	init();

	while (m_window.isOpen())
	{
		m_stateMachine.handleInput();
		m_stateMachine.update(0.0f);
		m_stateMachine.render();
	}
}

void Game::init()
{
	m_window.create(sf::VideoMode(1280, 720), "Game of Virus", sf::Style::Default);
	m_window.setFramerateLimit(60);

	m_stateMachine.init();
	m_stateMachine.add("mainMenu", &m_menu);
	m_stateMachine.add("gameWorld", &m_world);

	m_stateMachine.change("mainMenu", m_window);
}