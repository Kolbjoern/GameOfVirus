#include "Game.h"

#include "Globals.h"

#include <SFML\Window\Event.hpp>

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
	init();

	while (m_window.isOpen())
	{
		m_fpsCounter.tick();

		handleInput();

		update(m_fpsCounter.getDeltaTime());

		render();
	}
}

void Game::init()
{
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LDCompo40", sf::Style::Default);
	m_window.setFramerateLimit(FPS);
	m_fpsCounter.init(FPS);
}

void Game::handleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				break;
		}
	}
}

void Game::update(float deltaTime)
{

}

void Game::render()
{
	m_window.clear();

	m_window.display();
}