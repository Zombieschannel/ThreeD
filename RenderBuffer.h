#pragma once
#include "Error.h"
namespace DDD
{
	class RenderBuffer3D
	{
		friend class FrameBuffer3D;
		unsigned int ID = 0U;
		unsigned int internalFormat;
	public:
		~RenderBuffer3D()
		{
			GLCall(glDeleteRenderbuffers(1, &ID));
		}
		void create(const sf::Vector2u& size, const unsigned int internalFormat)
		{
			if (ID)
			{
				GLCall(glDeleteRenderbuffers(1, &ID));
			}
			GLCall(glGenRenderbuffers(1, &ID));
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, ID));
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, size.x, size.y));
		}
	};
}