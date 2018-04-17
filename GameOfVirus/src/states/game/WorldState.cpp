#include "WorldState.h"

#include "../../managers/StateMachine.h"

#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>

#include <iostream>

void WorldState::init(StateMachine& stateMachine, sf::RenderWindow& window)
{
	m_stateMachine = &stateMachine;
	m_window = &window;

	m_player.addFloat("x", 10.0f);
	m_player.addFloat("y", 0.0f);
	m_player.addFloat("width", 30.0f);
	m_player.addColor("bodyColor", sf::Color::Red);

	m_player.addComponent("input", &m_inputComponent);
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
	m_player.getComponent("input")->update(m_player, deltaTime);
}

void WorldState::render()
{
	m_window->clear(sf::Color::White);

	sf::CircleShape body;
	body.setRadius(m_player.getFloat("width")/2.0f);
	body.setFillColor(m_player.getColor("bodyColor"));
	body.setPosition(m_player.getFloat("x"), m_player.getFloat("y"));

	m_window->draw(body);

	m_window->display();
}

void WorldState::exit()
{

}