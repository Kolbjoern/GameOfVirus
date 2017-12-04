#pragma once

#include "IScreen.h"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

class MenuScreen : public IScreen
{
public:
	MenuScreen();
	~MenuScreen();

	virtual void run() override;
	virtual void destroy() override;

private:
	void init();
	void handleInput();
	void update();
	void render();

	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Text m_title;
	sf::Text m_navigate;

	bool m_showExplanation;
};

