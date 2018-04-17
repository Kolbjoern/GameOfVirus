#pragma once

#include "IGameState.h"
#include "../../objects/Object.h";
#include "../../components/InputComponent.h"

class WorldState : public IGameState
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

	Object m_player;
	InputComponent m_inputComponent;
};