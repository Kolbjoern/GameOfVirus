#include "WorldState.h"

#include "../../managers/StateMachine.h"

#include <SFML\Window\Event.hpp>

void WorldState::init(StateMachine& stateMachine, sf::RenderWindow& window)
{
	m_stateMachine = &stateMachine;
	m_window = &window;
}

void WorldState::handleInput()
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
					m_stateMachine->change("mainMenu");
				break;
		}
	}
}

void WorldState::update(float deltaTime)
{

}

void WorldState::render()
{
	m_window->clear(sf::Color::White);


	m_window->display();
}

void WorldState::exit()
{

}