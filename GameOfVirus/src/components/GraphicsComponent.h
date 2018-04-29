#pragma once

#include "Component.h"

#include <SFML\Graphics\Color.hpp>

#include <string>

class GraphicsComponent : public Component
{
public:
	GraphicsComponent(luabridge::LuaRef& componentTable);
	
	void setShape(const std::string& shape);
	void setColor(const sf::Color& color);

	std::string getShape() const;
	sf::Color getColor() const;

private:
	std::string m_shape;
	sf::Color m_color;
};

