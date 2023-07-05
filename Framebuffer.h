#pragma once
#include "Error.h"
#include "Texture.h"
#include "RenderBuffer.h"
#include "RenderTarget.h"
namespace DDD
{
	class FrameBuffer3D : public RenderTarget3D
	{
	public:
		enum Type
		{
			Color = GL_COLOR_ATTACHMENT0,
			Depth = GL_DEPTH_ATTACHMENT,
			Stencil = GL_STENCIL_ATTACHMENT,
#ifndef GLES20
			DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
#endif
		};
	private:
		unsigned int ID = 0U;
	public:
		~FrameBuffer3D()
		{
			GLCall(glDeleteFramebuffers(1, &ID));
		}
		void create()
		{
			if (ID)
			{
				GLCall(glDeleteFramebuffers(1, &ID));
			}
			GLCall(glGenFramebuffers(1, &ID));
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
		}
		void attachTexture(const Texture3D& texture, Type type)
		{
			if (!ID)
				return;
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, texture.ID, 0));
			texture.flipped = 1;
		}
		void attachRenderBuffer(const RenderBuffer3D& renderbuffer, Type type)
		{
			if (!ID)
				return;
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
			GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, renderbuffer.ID));
		}
		static void Bind(const FrameBuffer3D* framebuffer)
		{
			if (framebuffer)
			{
				GLCall(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->ID));
			}
			else
			{
				GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			}
		}
	};
}