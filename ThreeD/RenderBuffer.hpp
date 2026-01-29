#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/GlResource.hpp>
#include <cstdint>

namespace DDD
{
	class RenderBuffer3D : public sf::GlResource
	{
		friend class FrameBuffer3D;
		std::uint32_t ID;
		sf::Vector2u size;

	public:
		RenderBuffer3D();
		~RenderBuffer3D();

		std::uint32_t getHandle() const;
		void create(const sf::Vector2u size, const std::uint32_t internalFormat);
		const sf::Vector2u getSize() const;
	};
}
