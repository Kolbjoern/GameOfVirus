#pragma once

#include "IGameState.h"

#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

class MenuState : public IGameState
{
public:
	virtual void init(StateMachine& stateMachine, sf::RenderWindow& window) override;
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void render() override;
	virtual void exit() override;

private:
	StateMachine* m_stateMachine;

	sf::RenderWindow* m_window;

	sf::Font m_font;
	sf::Text m_text;
};

