#include "GraphicsComponent.h"

#include "../utils/LuaFunctions.h"

#include "LuaBridge.h"

#include <unordered_map>
#include <vector>
#include <iostream>
#include <map>

GraphicsComponent::GraphicsComponent(luabridge::LuaRef& componentTable)
{
	luabridge::LuaRef shapeRef = componentTable["shape"];
	luabridge::LuaRef colorRef = componentTable["color"];
	
	if (shapeRef.isString())
		m_shape = shapeRef.cast<std::string>();
	else
		std::cout << "Error, GraphicsComponent.shape is not a string" << std::endl;

	if (colorRef.isTable())
	{
		auto red =		colorRef["red"];
		auto green =	colorRef["green"];
		auto blue =		colorRef["blue"];
		auto alpha =	colorRef["alpha"];

		if (red.isNumber())
			m_color.r = red.cast<int>();

		if (green.isNumber())
			m_color.g = green.cast<int>();

		if (blue.isNumber())
			m_color.b = blue.cast<int>();

		if (alpha.isNumber())
			m_color.a = alpha.cast<int>();
	}
	else
		std::cout << "Error, GraphicsComponent.color is not a string" << std::endl;
}

void GraphicsComponent::setShape(const std::string& shape)
{
	m_shape = shape;
}

void GraphicsComponent::setColor(const sf::Color & color)
{
	m_color = color;
}

std::string GraphicsComponent::getShape() const
{
	return m_shape;
}

sf::Color GraphicsComponent::getColor() const
{
	return m_color;
}