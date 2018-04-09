#include "Game.h"

#include <SFML\Window\Event.hpp>

void Game::run()
{
	init();

	while (m_window.isOpen())
	{
		m_loopTimer.tick();
		
		m_stateMachine.handleInput();
		m_stateMachine.update(m_loopTimer.getDeltaTime());
		m_stateMachine.render();
	}
}

void Game::init()
{
	m_window.create(sf::VideoMode(1280, 720), "Game of Virus", sf::Style::Default);
	m_window.setFramerateLimit(60);

	m_menu.init(m_stateMachine, m_window);
	m_world.init(m_stateMachine, m_window);

	m_stateMachine.init(m_window);
	m_stateMachine.add("mainMenu", m_menu);
	m_stateMachine.add("gameWorld", m_world);

	m_stateMachine.change("mainMenu");

	m_loopTimer.init();
}