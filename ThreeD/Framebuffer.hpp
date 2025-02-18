#pragma once
#include <cstdint>
#include "Error.hpp"
#include "Texture.hpp"
#include "RenderBuffer.hpp"
#include "RenderTarget.hpp"

#ifndef GL_DEPTH_STENCIL_ATTACHMENT
	#define GL_DEPTH_STENCIL_ATTACHMENT -1
#endif

namespace DDD
{
	class FrameBuffer3D : public RenderTarget3D
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
		std::uint32_t ID = 0U;
	public:
		~FrameBuffer3D();
		void create();
		void attachTexture(const Texture3D& texture, Type type);
		void attachRenderBuffer(const RenderBuffer3D& renderbuffer, Type type);
		static void Bind(const FrameBuffer3D* framebuffer);
	};
}