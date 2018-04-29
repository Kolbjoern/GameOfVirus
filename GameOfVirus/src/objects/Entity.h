#pragma once

#include "../components/Component.h"

#include <string>
#include <typeindex>
#include <unordered_map>

enum Type
{
	STRING,
	FLOAT
};

struct Variant
{
	Variant() {};
	Variant(Variant && other) {};
	~Variant() {};

	Type type;

	union
	{
		std::string str;
		float f;
	};
};

class Entity
{
public:
	~Entity();

	void addComponent(std::type_index type, Component* component);
	void addString(std::string name, std::string value);
	void addFloat(std::string name, float value);
	void setType(const std::string& type);

	std::string getString(std::string name) const;
	float getFloat(std::string name) const;
	std::string getType() const;

	template <typename T>
	T* getComponent()
	{
		auto it = m_components.find(std::type_index(typeid(T)));

		if (it != m_components.end())
			return dynamic_cast<T*>(it->second);

		return nullptr;
	};

private:
	std::string m_type;
	std::unordered_map<std::type_index, Component*> m_components;
	std::unordered_map<std::string, Variant> m_properties;
};

