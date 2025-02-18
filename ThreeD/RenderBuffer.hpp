#pragma once
#include <SFML/System.hpp>
#include <cstdint>

namespace DDD
{
	class RenderBuffer3D
	{
		friend class FrameBuffer3D;
		std::uint32_t ID;
	public:
		RenderBuffer3D();
		~RenderBuffer3D();
		void create(const sf::Vector2u size, const std::uint32_t internalFormat);
	};
}