#pragma once
#include "OGL.h"
#include "Error.h"
namespace DDD
{
	class LayoutBuffer3D
	{
	public:
		static void Bind(unsigned int layout, unsigned int componentCount, unsigned int stride, unsigned int offset)
		{
			GLCall(glEnableVertexAttribArray(layout));
			GLCall(glVertexAttribPointer(layout, componentCount, GL_FLOAT, GL_FALSE, stride, (const void*)offset));
		}
	};
}