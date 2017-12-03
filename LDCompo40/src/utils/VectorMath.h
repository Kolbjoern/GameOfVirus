#pragma once

#include <SFML\System\Vector2.hpp>

class VectorMath
{
public:
	static sf::Vector2f normalize(sf::Vector2f vec);
	static sf::Vector2f rotate(sf::Vector2f vec, const float& angleRadians);
	static float getMagnitude(sf::Vector2f vec);

private:
	VectorMath() {} // disallow object creation
};

