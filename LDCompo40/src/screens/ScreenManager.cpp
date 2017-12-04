#include "ScreenManager.h"

void ScreenManager::changeScreen(IScreen* newScreen)
{
	if (m_currentScreen != nullptr)
	{
		m_currentScreen->destroy();
		m_currentScreen = nullptr;
	}

	m_currentScreen = newScreen;
	m_currentScreen->run();
}