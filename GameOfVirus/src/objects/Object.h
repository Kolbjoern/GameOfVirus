#pragma once

#include "../components/IComponent.h"

#include <SFML\Graphics\Color.hpp>

#include <unordered_map>

enum Type
{
	STRING,
	FLOAT,
	COLOR,
	COMPONENT
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
		float fl;
		sf::Color clr;
		IComponent* comp;
	};
};

class Object
{
public:
	void addString(std::string name, std::string value);
	void addFloat(std::string name, float value);
	void addColor(std::string name, sf::Color color);
	void addComponent(std::string name, IComponent* component);

	std::string getString(std::string name);
	float getFloat(std::string name);
	sf::Color getColor(std::string name);
	IComponent* getComponent(std::string name);

private:
	std::unordered_map<std::string, Variant> m_properties;
};