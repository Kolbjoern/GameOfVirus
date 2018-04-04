#pragma once

#include "IGameState.h"

class WorldState : public IGameState
{
public:
	virtual void init(sf::RenderWindow& window) override;
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void render() override;
	virtual void exit() override;

private:
	sf::RenderWindow* m_window;
};

