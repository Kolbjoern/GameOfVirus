#include "StateMachine.h"

void StateMachine::init(sf::RenderWindow& window)
{
	m_currentState = nullptr;
	m_window = &window;
}

void StateMachine::handleInput()
{
	m_currentState->handleInput();
}

void StateMachine::update(float deltaTime)
{
	m_currentState->update(deltaTime);
}

void StateMachine::render()
{
	m_currentState->render();
}

void StateMachine::add(std::string name, IGameState& state)
{
	m_states[name] = &state;
}

void StateMachine::change(std::string name)
{
	if (m_currentState != nullptr)
		m_currentState->exit();

	m_currentState = m_states.at(name);
}