#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>
#include "Transform.hpp"

namespace DDD
{
	static const float dot(const sf::Vector3f vec1, const sf::Vector3f vec2);
	static const float dot(const sf::Vector2f vec1, const sf::Vector2f vec2);
	static const sf::Vector3f cross(const sf::Vector3f vec1, const sf::Vector3f vec2);
	static const float length(const sf::Vector3f vec1);
	static const float length(const sf::Vector2f vec1);
	static const sf::Vector3f normalize(const sf::Vector3f vec1);
	static const sf::Vector2f normalize(const sf::Vector2f vec1);
	static const Transform3D lookAt(const sf::Vector3f eye, const sf::Vector3f center, const sf::Vector3f up);
	static const sf::Vector3f calculateNormal(const sf::Vector3f point1, const sf::Vector3f point2, const sf::Vector3f point3);
}