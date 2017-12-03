#include "VectorMath.h"

#include <math.h>

sf::Vector2f VectorMath::normalize(sf::Vector2f vec)
{
	float mag = getMagnitude(vec);
	sf::Vector2f norm;

	norm.x = vec.x / mag;
	norm.y = vec.y / mag;

	return norm;
}

sf::Vector2f VectorMath::rotate(sf::Vector2f vec, const float& angleRadians)
{
	sf::Vector2f result;

	result.x = vec.x * cosf(angleRadians) - vec.y * sinf(angleRadians);
	result.y = vec.x * sinf(angleRadians) + vec.y * cosf(angleRadians);

	return result;
}

float VectorMath::getMagnitude(sf::Vector2f vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}