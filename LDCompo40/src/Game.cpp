#include "Game.h"

#include "Globals.h"
#include "components\PhysicsComponent.h"
#include "components\ControllerComponent.h"
#include "utils\RandomNumGen.h"
#include "screens/ScreenManager.h"
#include "screens/MenuScreen.h"

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

	m_done = false;

	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LDCompo40", sf::Style::Default);
	m_window.setFramerateLimit(FPS);
	m_fpsCounter.init(FPS);

	m_camera = m_window.getDefaultView();

	m_world.init(TILE_SIZE, WORLD_WIDTH, WORLD_HEIGHT);

	m_player.init(15.0f, sf::Vector2f(120.0f, 100.0f));
	m_world.createGroundMass(120.0f / TILE_SIZE, 100.0f / TILE_SIZE, 10.0f);

	m_virus.init(400, 200, &m_world);
	//m_virus.startSpreading();

	//m_shape.setPosition(20.0f, 40.0f);
	m_shape.init("src/shapeFiles/kShape.tish", sf::Vector2i(10, 10));

	Gun rapid;
	rapid.init("[1] Rapid", 5.0f, 0.05f, 1, 10.0f, 600.0f, 8.0f);
	m_guns.push_back(rapid);

	Gun spread;
	spread.init("[2] Spray", 7.5f, 0.05f, 10, 20.0f, 400.0f, 8.0f);
	m_guns.push_back(spread);

	Gun threeSixty;
	threeSixty.init("[3] 360", 3.0f, 0.01f, 30, 180.0f, 1400.0f, 0.02f);
	m_guns.push_back(threeSixty);

	if (m_font.loadFromFile("assets/font/prstartk.ttf"))
	{
		m_infoText.setFont(m_font);
		m_infoText.setCharacterSize(25);
		m_infoText.setFillColor(sf::Color::Red);
		m_infoText.setString("Virus is not isolated!");

		for (int i = 0; i < m_guns.size(); i++)
		{
			sf::Text wepTxt;
			wepTxt.setFont(m_font);
			wepTxt.setCharacterSize(18);
			wepTxt.setFillColor(sf::Color::Cyan);
			wepTxt.setString(m_guns[i].getName());
			m_wepTxt.push_back(wepTxt);
		}
	}
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

			case sf::Event::KeyReleased:
				//if (event.key.code == sf::Keyboard::Escape)
				//	ScreenManager::getInstance().changeScreen(new MenuScreen());
				break;
		}
	}
}

void Game::update(float deltaTime)
{
	//m_world.update(deltaTime);
	m_virus.update(deltaTime);
	m_shape.update(m_world);

	if (m_virus.getIsIsolated())
	{
		m_infoText.setFillColor(sf::Color::Green);
		m_infoText.setString("Virus is isolated! Now destroy it!");
	}

	if (m_virus.getIsDestroyed())
	{
		m_infoText.setFillColor(sf::Color::Blue);

		static int elapsed = (int)m_fpsCounter.getElapsedTime();
		m_infoText.setCharacterSize(20);
		m_infoText.setPosition((m_camera.getCenter().x - m_camera.getSize().x / 2.0f + 150.0f), m_camera.getCenter().y - m_camera.getSize().y / 2 + 5.0f);
		m_infoText.setString("YOU WON! Elapsed time: " + std::to_string(elapsed) + "s");
	}

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

	m_infoText.setPosition((m_camera.getCenter().x - m_camera.getSize().x / 2.0f + 300.0f), m_camera.getCenter().y - m_camera.getSize().y / 2 + 5.0f);

	if (m_player.getCurrentGunIndex() >= 0 && m_player.getCurrentGunIndex() < m_wepTxt.size())
	{
		for (int i = 0; i < m_wepTxt.size(); i++)
		{
			if (i == m_player.getCurrentGunIndex())
				m_wepTxt[i].setFillColor(sf::Color::Red);
			else
				m_wepTxt[i].setFillColor(sf::Color::Cyan);

			m_wepTxt[i].setPosition((m_camera.getCenter().x - m_camera.getSize().x / 2.0f), m_camera.getCenter().y - m_camera.getSize().y / 2 + (20.0f * i));
		}
	}
}

void Game::render()
{
	m_window.clear();

	m_world.draw(m_window, m_camera);

	m_player.draw(m_window);

	//m_window.draw(m_shape);

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i].draw(m_window);
	}

	m_window.draw(m_infoText);

	for (int i = 0; i < m_wepTxt.size(); i++)
	{
		m_window.draw(m_wepTxt[i]);
	}

	m_window.display();
}