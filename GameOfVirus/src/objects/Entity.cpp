#include "Entity.h"

#include "../components/Component.h"

Entity::~Entity()
{
	for (auto& comp : m_components)
	{
		delete comp.second;
	}
}

void Entity::addComponent(std::type_index type, Component* component)
{
	m_components[type] = component;
}

void Entity::addString(std::string name, std::string value)
{
	m_properties.emplace(name, Variant());
	m_properties.at(name).type = Type::STRING;
	m_properties.at(name).str = value;
}

void Entity::addFloat(std::string name, float value)
{
	m_properties.emplace(name, Variant());
	m_properties.at(name).type = Type::FLOAT;
	m_properties.at(name).f = value;
}

void Entity::setType(const std::string& type)
{
	m_type = type;
}

std::string Entity::getString(std::string name) const
{
	if (m_properties.at(name).type != Type::STRING)
		return "";

	return m_properties.at(name).str;
}

float Entity::getFloat(std::string name) const
{
	if (m_properties.at(name).type != Type::FLOAT)
		return 0.0f;

	return m_properties.at(name).f;
}

std::string Entity::getType() const
{
	return m_type;
}
