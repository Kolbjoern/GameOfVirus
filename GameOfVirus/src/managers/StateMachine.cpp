#include "StateMachine.h"

void StateMachine::init()
{
	m_currentState = nullptr;
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

void StateMachine::add(std::string name, IGameState* state)
{
	m_states[name] = state;
}

void StateMachine::change(std::string name, sf::RenderWindow& window)
{
	if (m_currentState != nullptr)
		m_currentState->exit();

	m_currentState = m_states.at(name);
	m_currentState->init(window);
}