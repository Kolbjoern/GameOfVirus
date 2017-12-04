#pragma once

#include "IScreen.h"

class ScreenManager
{
public:
	static ScreenManager& getInstance()
	{
		static ScreenManager instance;

		return instance;
	}

	void changeScreen(IScreen* newScreen);

private:
	ScreenManager() {};
	ScreenManager(ScreenManager const&);

	IScreen* m_currentScreen = nullptr;
};

