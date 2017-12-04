#include "Game.h"

#include "screens\ScreenManager.h"
#include "screens\MenuScreen.h"

Game::Game()
{
}

Game::~Game()
{

}

void Game::run()
{
	ScreenManager::getInstance().changeScreen(new MenuScreen());
}
