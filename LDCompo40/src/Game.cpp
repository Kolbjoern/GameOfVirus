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

	m_camera = m_window.getDefaultView();

	m_world.init(TILE_SIZE, WORLD_WIDTH, WORLD_HEIGHT);

	m_player.init(15.0f);
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
		m_world.createHole((pixelPos.x + m_camera.getCenter().x - m_camera.getSize().x/2)/TILE_SIZE, 
			 (pixelPos.y + m_camera.getCenter().y - m_camera.getSize().y/2)/TILE_SIZE, 5.0f);
	}

	m_player.update(m_world.getData(), m_camera, deltaTime);

	if (m_camera.getCenter() != m_player.getPosition())
	{
		sf::Vector2f playerPos = m_player.getPosition();
		m_camera.setCenter(m_player.getPosition());
		m_window.setView(m_camera);
	}
}

void Game::render()
{
	m_window.clear();

	m_world.draw(m_window, m_camera);
	m_player.draw(m_window);

	m_window.display();
}