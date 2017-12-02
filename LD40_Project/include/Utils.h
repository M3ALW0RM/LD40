#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>

#define PI 3.14159265358979323846f

namespace vec
{

inline float magnitude(const sf::Vector2f& vec)
{
	return (float)sqrt(vec.x * vec.x + vec.y * vec.y);
}

inline void normalize(sf::Vector2f& vec)
{
	double mag = magnitude(vec);
	vec.x /= mag;
	vec.y /= mag;
}

inline float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline float angleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2, bool inDegrees = false)
{
	float angle = acos(dotProduct(v1, v2) / (magnitude(v1) * magnitude(v2)));
	if (inDegrees)
		angle = angle * 180.f / PI;

	return angle;
}

}