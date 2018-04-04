#include "WorldState.h"

#include <SFML\Window\Event.hpp>

void WorldState::init(sf::RenderWindow& window)
{
	m_window = &window;
}

void WorldState::handleInput()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();
	}
}

void WorldState::update(float deltaTime)
{

}

void WorldState::render()
{
	m_window->clear();


	m_window->display();
}

void WorldState::exit()
{

}