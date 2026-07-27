#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cstdint>
#include "ColorF.hpp"
#include "VertexComponent.hpp"

namespace DDD
{
	struct Vertex3D
	{
		sf::Vector3f position;
		ColorF color;
		sf::Vector2f texCoord;

		Vertex3D();
		Vertex3D(sf::Vector3f pos);
		Vertex3D(sf::Vector3f pos, ColorF col);
		Vertex3D(sf::Vector3f pos, ColorF col, sf::Vector2f tex);
		~Vertex3D();

		static std::uint8_t componentCount(std::uint8_t component);
		static Component componentType(std::uint8_t component);
	};
}