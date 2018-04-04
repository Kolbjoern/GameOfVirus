#pragma once

#include "../states/game/IGameState.h"

#include <SFML\Graphics\RenderWindow.hpp>

#include <string>
#include <unordered_map>

class StateMachine
{
public:
	void init();
	void handleInput();
	void update(float deltaTime);
	void render();

	void add(std::string name, IGameState* state);
	void change(std::string name, sf::RenderWindow& window/*TODO::ADD optional parameters*/);

	std::unordered_map<std::string, IGameState*> m_states;
	IGameState* m_currentState;
};