#include "Game.h"

#include "Globals.h"
#include "components\PhysicsComponent.h"
#include "components\ControllerComponent.h"
#include "utils\RandomNumGen.h"

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
	RandomNumGen::getInstance().init(1337);

	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LDCompo40", sf::Style::Default);
	m_window.setFramerateLimit(FPS);
	m_fpsCounter.init(FPS);

	m_camera = m_window.getDefaultView();

	m_world.init(TILE_SIZE, WORLD_WIDTH, WORLD_HEIGHT);

	m_player.init(15.0f, sf::Vector2f(120.0f, 100.0f));

	Gun rapid;
	rapid.init("Rapid", 5.0f, 0.05f, 1, 10.0f, 600.0f, 8.0f);
	m_guns.push_back(rapid);

	Gun spread;
	spread.init("Spread", 7.5f, 0.8f, 15, 35.0f, 350.0f, 8.0f);
	m_guns.push_back(spread);

	Gun threeSixty;
	threeSixty.init("360", 3.0f, 0.01f, 30, 180.0f, 1400.0f, 0.02f);
	m_guns.push_back(threeSixty);
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
			
			case sf::Event::Resized:
				m_camera.setSize(sf::Vector2f((float)event.size.width, (float)event.size.height));
				m_window.setView(m_camera);
				break;
		}
	}
}

void Game::update(float deltaTime)
{
	m_world.update(deltaTime);

	m_player.update(m_world, m_window, m_camera, m_guns, m_projectiles, deltaTime);

	if (m_camera.getCenter() != m_player.getPosition())
	{
		sf::Vector2f playerPos = m_player.getPosition();
		m_camera.setCenter(m_player.getPosition());
		m_window.setView(m_camera);
	}

	for (int i = 0; i < m_projectiles.size(); )
	{
		m_projectiles[i].update(m_world, m_window, m_camera, deltaTime);

		if (m_projectiles[i].getIsDead())
		{
			m_projectiles[i] = m_projectiles.back();
			m_projectiles.pop_back();
		}
		else
			i++;
	}
}

void Game::render()
{
	m_window.clear();

	m_world.draw(m_window, m_camera);

	m_player.draw(m_window);
	
	for (int i = 0; i < m_projectiles.size(); i++)	
	{
		m_projectiles[i].draw(m_window);
	}

	m_window.display();
}