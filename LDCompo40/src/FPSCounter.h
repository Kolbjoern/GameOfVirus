#pragma once

#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\System\Sleep.hpp>

class FPSCounter
{
public:
	FPSCounter();
	~FPSCounter();

	void init(float maxFps);
	void setMaxFps(float maxFps);
	void tick();

	float getCurrentFPS();
	float getDeltaTime();
	float getElapsedTime();

private:
	float m_fps;

	float m_maxFps;
	sf::Clock m_clock;
	sf::Time m_elapsed;
	sf::Time m_previous;
};

