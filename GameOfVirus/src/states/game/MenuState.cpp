#include "MenuState.h"

#include "../../managers/StateMachine.h"

#include <SFML\Window\Event.hpp>

void MenuState::init(StateMachine& stateMachine, sf::RenderWindow& window)
{
	m_stateMachine = &stateMachine;
	m_window = &window;

	if (m_font.loadFromFile("assets/font/prstartk.ttf"))
	{
		m_text.setFont(m_font);
		m_text.setCharacterSize(60);
		m_text.setFillColor(sf::Color::White);
		m_text.setString("Game of Virus");
		sf::FloatRect rectBounds =  m_text.getLocalBounds();
		m_text.setPosition(1280.0f/2 - rectBounds.width/2, 250.0f); //positioning at centre
	}
}

void MenuState::handleInput()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window->close();
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Num1)
					m_stateMachine->change("gameWorld");
				break;
		}
	}
}

void MenuState::update(float deltaTime)
{

}

void MenuState::render()
{
	m_window->clear();

	m_window->draw(m_text);

	m_window->display();
}

void MenuState::exit()
{
	
}