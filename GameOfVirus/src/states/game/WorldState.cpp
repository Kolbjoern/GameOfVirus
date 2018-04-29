#include "WorldState.h"

#include "../../managers/StateMachine.h"
#include "../../components/GraphicsComponent.h"
#include "../../components/InputComponent.h"
#include "../../utils/LuaFunctions.h"
#include "../../utils/EntityFunctions.h"

#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>

#include <iostream>

void WorldState::init(StateMachine& stateMachine, sf::RenderWindow& window)
{
	m_stateMachine = &stateMachine;
	m_window = &window;
	
	luabridge::lua_State* L = luabridge::luaL_newstate();
	luabridge::luaL_openlibs(L);

	LuaFunctions::loadScript(L, "scripts/objects/objectList.lua");
	LuaFunctions::loadGetKeysFunction(L);

	m_ent = EntityFunctions::loadEntity(L, "player");
	m_ent->addFloat("width", 30.0f);
	m_ent->addFloat("x", 60.0f);
	m_ent->addFloat("y", 10.0f);

	luabridge::lua_close(L);
}

void WorldState::handleInput()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window->close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::M:
						m_stateMachine->change("mainMenu");
						break;

					case sf::Keyboard::Escape:
						m_window->close();
						break;
				}
				break;
		}
	}
}

void WorldState::update(float deltaTime)
{
	auto inputComp = m_ent->getComponent<InputComponent>();
	inputComp->update(*m_ent, deltaTime);
}

void WorldState::render()
{
	m_window->clear(sf::Color::White);
	
	auto gc = m_ent->getComponent<GraphicsComponent>();
	if (gc->getShape() == "circle")
	{
		sf::CircleShape body1;
		body1.setRadius(m_ent->getFloat("width") / 2.0f);
		body1.setPosition(m_ent->getFloat("x"), m_ent->getFloat("y"));
		body1.setFillColor(gc->getColor());

		m_window->draw(body1);
	}
	
	m_window->display();
}

void WorldState::exit()
{

}