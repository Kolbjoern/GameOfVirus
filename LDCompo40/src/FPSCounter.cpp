#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::init(float maxFps)
{
	setMaxFps(maxFps);

	m_previous = m_clock.getElapsedTime();
}

void FPSCounter::setMaxFps(float maxFps)
{
	m_maxFps = maxFps;
}

void FPSCounter::tick()
{
	static const int NUM_SAMPLES = 100;
	static sf::Time elapsedTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	sf::Time current = m_clock.getElapsedTime();
	m_elapsed = current - m_previous;

	elapsedTimes[currentFrame % NUM_SAMPLES] = m_elapsed;

	m_previous = current;

	currentFrame++;

	int counter;
	if (currentFrame < NUM_SAMPLES)
		counter = currentFrame;
	else
		counter = NUM_SAMPLES;

	sf::Time elapsedAverage = sf::seconds(0.0f);

	for (int i = 0; i < counter; i++)
	{
		elapsedAverage += elapsedTimes[i];
	}
	elapsedAverage = sf::seconds(elapsedAverage.asSeconds() / counter);

	if (elapsedAverage.asSeconds() > 0.0f)
		m_fps = 1.0f / elapsedAverage.asSeconds();
	else
		m_fps = 60.0f; // only a filler for the very first frame!

	//if (1000.0f / m_maxFps > (float)m_elapsed.asMilliseconds())
	//	sf::sleep(sf::milliseconds(1000.0f / m_maxFps - (float)m_elapsed.asMilliseconds()));
}

float FPSCounter::getCurrentFPS()
{
	return m_fps;
}

float FPSCounter::getDeltaTime()
{
	return m_elapsed.asSeconds();
}

float FPSCounter::getElapsedTime()
{
	return m_clock.getElapsedTime().asSeconds();
}