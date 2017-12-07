#include "MenuScreen.h"

#include "ScreenManager.h"
#include "../Globals.h"

#include <SFML\Window\Event.hpp>

MenuScreen::MenuScreen()
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::run()
{
	init();

	while (m_window.isOpen())
	{
		handleInput();

		update();

		render();
	}
	handleInput();
}

void MenuScreen::init()
{
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LDCompo40", sf::Style::Close);
	m_window.setFramerateLimit(FPS);
	m_window.setKeyRepeatEnabled(false);

	if (m_font.loadFromFile("assets/font/prstartk.ttf"))
	{
		m_title.setFont(m_font);
		m_title.setCharacterSize(40);
		m_title.setFillColor(sf::Color::White);
		m_title.setString("Game of Virus");
		m_title.setPosition(350.0f, 300.0f);

		m_navigate.setFont(m_font);
		m_navigate.setCharacterSize(18);
		m_navigate.setFillColor(sf::Color::White);
		m_navigate.setString("press [1] to continue...");
		m_navigate.setPosition(800.0f,  650.0f);
	}

	m_showExplanation = false;
}

void MenuScreen::handleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Num1)
				{
					if (!m_showExplanation)
					{
						m_title.setPosition(50.0f, 50.0f);
						m_title.setCharacterSize(25);
						m_title.setString(
							"A virus is spreading through your cave!\n\n"
							"Find it, isolate it and THEN destroy it.\n\n\n\n"
							"Left click: destroy\n\n"
							"Right click: create mass\n\n\n\n\n\n"
							"You can't lose in this game,\n\nonly win or give up. ;)");
						m_showExplanation = true;
					}
					else
					{
						//ScreenManager::getInstance().changeScreen(new GamePlayScreen());
					}
				}
				break;
		}
	}
}

void MenuScreen::update()
{
	
}

void MenuScreen::render()
{
	m_window.clear();

	m_window.draw(m_title);
	m_window.draw(m_navigate);

	m_window.display();
}

void MenuScreen::destroy()
{
	m_window.close();
}