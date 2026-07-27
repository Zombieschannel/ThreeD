#pragma once
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include "Error.hpp"
#include "Texture.hpp"
#include "RenderBuffer.hpp"
#include "RenderTarget.hpp"

namespace DDD
{
	class FrameBuffer3D : public RenderTarget3D, public sf::RenderTarget
	{
	public:
		enum class Type
		{
			Color = GL_COLOR_ATTACHMENT0,
			Depth = GL_DEPTH_ATTACHMENT,
			Stencil = GL_STENCIL_ATTACHMENT,
			DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
		};
	private:
		std::uint32_t ID = 0;
		sf::Vector2u size;
	public:
		using RenderTarget::draw;
		using RenderTarget3D::draw;
		FrameBuffer3D();
		~FrameBuffer3D();

		std::uint32_t getHandle() const;
		void attachTexture(const Texture3D& texture, Type type);
		void attachRenderBuffer(const RenderBuffer3D& renderbuffer, Type type);
		virtual sf::Vector2u getSize() const;
	};
	void BindFrameBuffer(const FrameBuffer3D* framebuffer);
}