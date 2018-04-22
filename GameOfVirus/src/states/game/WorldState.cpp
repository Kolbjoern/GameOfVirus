#include "WorldState.h"

#include "../../managers/StateMachine.h"

#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>

#include <iostream>

void WorldState::init(StateMachine& stateMachine, sf::RenderWindow& window)
{
	m_stateMachine = &stateMachine;
	m_window = &window;

	m_object1.addFloat("x", 10.0f);
	m_object1.addFloat("y", 0.0f);
	m_object1.addFloat("width", 30.0f);
	m_object1.addColor("bodyColor", sf::Color::Red);
	m_object1.addComponent("input", &m_inputComponent);

	m_object2.addFloat("x", 60.0f);
	m_object2.addFloat("y", 0.0f);
	m_object2.addFloat("width", 30.0f);
	m_object2.addColor("bodyColor", sf::Color::Blue);

	m_object3.addFloat("x", 10.0f);
	m_object3.addFloat("y", 50.0f);
	m_object3.addFloat("width", 30.0f);
	m_object3.addColor("bodyColor", sf::Color::Green);
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
				switch (event.key.code)
				{
					case sf::Keyboard::M:
						m_stateMachine->change("mainMenu");
						break;

					case sf::Keyboard::Escape:
						m_window->close();
						break;

					case sf::Keyboard::Num1:
						if (m_object1.getComponent("input") == nullptr)
							m_object1.addComponent("input", &m_inputComponent);
						else
							m_object1.addComponent("input", nullptr);
						break;

					case sf::Keyboard::Num2:
						if (m_object2.getComponent("input") == nullptr)
							m_object2.addComponent("input", &m_inputComponent);
						else
							m_object2.addComponent("input", nullptr);
						break;

					case sf::Keyboard::Num3:
						if (m_object3.getComponent("input") == nullptr)
							m_object3.addComponent("input", &m_inputComponent);
						else
							m_object3.addComponent("input", nullptr);
						break;
				}
				break;
		}
	}
}

void WorldState::update(float deltaTime)
{
	if (m_object1.getComponent("input") != nullptr)
		m_object1.getComponent("input")->update(m_object1, deltaTime);

	if (m_object2.getComponent("input") != nullptr)
		m_object2.getComponent("input")->update(m_object2, deltaTime);

	if (m_object3.getComponent("input") != nullptr)
		m_object3.getComponent("input")->update(m_object3, deltaTime);
}

void WorldState::render()
{
	m_window->clear(sf::Color::White);

	sf::CircleShape body1;
	body1.setRadius(m_object1.getFloat("width") / 2.0f);
	body1.setFillColor(m_object1.getColor("bodyColor"));
	body1.setPosition(m_object1.getFloat("x"), m_object1.getFloat("y"));
	m_window->draw(body1);

	sf::CircleShape body2;
	body2.setRadius(m_object2.getFloat("width")/2.0f);
	body2.setFillColor(m_object2.getColor("bodyColor"));
	body2.setPosition(m_object2.getFloat("x"), m_object2.getFloat("y"));
	m_window->draw(body2);

	sf::CircleShape body3;
	body3.setRadius(m_object3.getFloat("width") / 2.0f);
	body3.setFillColor(m_object3.getColor("bodyColor"));
	body3.setPosition(m_object3.getFloat("x"), m_object3.getFloat("y"));
	m_window->draw(body3);
	
	m_window->display();
}

void WorldState::exit()
{

}