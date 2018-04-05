#pragma once

#include "../states/game/IGameState.h"

#include <SFML\Graphics\RenderWindow.hpp>

#include <string>
#include <unordered_map>

class StateMachine
{
public:
	void init(sf::RenderWindow& window);
	void handleInput();
	void update(float deltaTime);
	void render();

	void add(std::string name, IGameState& state);
	void change(std::string name/*TODO::ADD optional parameters*/);

	IGameState* m_currentState;

	sf::RenderWindow* m_window;

	std::unordered_map<std::string, IGameState*> m_states;
};