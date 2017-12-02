#include "Game.h"

#include "Globals.h"
#include "components\PhysicsComponent.h"
#include "components\InputComponent.h"

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

		if (m_window.hasFocus())
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

	m_player.init(15.0f, sf::Color::Red, new InputComponent(), new PhysicsComponent());
	m_player.setPosition(sf::Vector2f(120.0f, 100.0f));
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f mouseDir = sf::Vector2f((pixelPos.x + m_camera.getCenter().x - m_camera.getSize().x / 2), (pixelPos.y + m_camera.getCenter().y - m_camera.getSize().y / 2));
		sf::Vector2f centerDir = m_player.getPosition() + sf::Vector2f(m_player.getRadius() / 2.0f, m_player.getRadius() / 2.0f);
		sf::Vector2f direction = mouseDir - centerDir;
		float directionLength = sqrt(direction.x * direction.x + direction.y * direction.y);
		sf::Vector2f normalized;

		if (directionLength != 0)
		{
			normalized.x = direction.x / directionLength;
			normalized.y = direction.y / directionLength;
		}
		
		Entity p;
		p.init(3.0f, sf::Color::Magenta, nullptr, new PhysicsComponent());
		p.setPosition(centerDir);
		p.setAcceleration(500.0f * normalized);
		p.setIsBullet(true);
		m_projectiles.emplace_back(p);
	}

	m_player.update(m_world, m_window, m_camera, deltaTime);

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

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i].draw(m_window);
	}

	m_player.draw(m_window);

	m_window.display();
}