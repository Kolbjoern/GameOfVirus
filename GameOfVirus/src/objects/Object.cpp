#include "Object.h"

void Object::addString(std::string name, std::string value)
{
	m_properties.emplace(name, Variant());
	m_properties.at(name).type = Type::STRING;
	m_properties.at(name).str = value;
}

void Object::addFloat(std::string name, float value)
{
	m_properties.emplace(name, Variant());
	m_properties.at(name).type = Type::FLOAT;
	m_properties.at(name).fl = value;
};

void Object::addColor(std::string name, sf::Color color)
{
	m_properties.emplace(name, Variant());
	m_properties.at(name).type = Type::COLOR;
	m_properties.at(name).clr = color;
}

void Object::addComponent(std::string name, IComponent* component)
{
	m_properties.emplace(name, Variant());
	m_properties.at(name).type = Type::COMPONENT;
	m_properties.at(name).comp = component;
}

std::string Object::getString(std::string name)
{
	if (m_properties.at(name).type != Type::STRING)
		return "";

	return m_properties.at(name).str;
}

float Object::getFloat(std::string name)
{
	if (m_properties.at(name).type != Type::FLOAT)
		return 0.0f;

	return m_properties.at(name).fl;
}

sf::Color Object::getColor(std::string name)
{
	if (m_properties.at(name).type != Type::COLOR)
		return sf::Color::Black;

	return m_properties.at(name).clr;
}

IComponent* Object::getComponent(std::string name)
{
	if (m_properties.find(name) == m_properties.end())
		return nullptr;

	if (m_properties.at(name).type != Type::COMPONENT)
		return nullptr;

	return m_properties.at(name).comp;
}