#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>
#include "Transform.hpp"

namespace DDD
{
	std::array<float, 9> getMat3(const Transform3D& m);
	std::array<float, 9> getInverseMat3(const std::array<float, 9>& m);
	std::array<float, 9> getTransposedMat3(const std::array<float, 9>& m);
	Transform3D lookAt(sf::Vector3f eye, sf::Vector3f center, sf::Vector3f up);
	sf::Vector3f calculateNormal(sf::Vector3f point1, sf::Vector3f point2, sf::Vector3f point3);
}