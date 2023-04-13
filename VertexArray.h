#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
namespace DDD
{
	class VertexArray3D
	{
		unsigned int ID;
		IndexBuffer3D* indexBuffer = nullptr;
		VBO* vertexBuffer = nullptr;
		void setBuffers()
		{
#if not defined(GLES20)
			if (ID)
			{
				GLCall(glDeleteVertexArrays(1, &ID));
			}
			GLCall(glGenVertexArrays(1, &ID));
			GLCall(glBindVertexArray(ID));
#endif

			VBO::BufferData(*vertexBuffer);
			if (indexBuffer)
				IndexBuffer3D::BufferData(*indexBuffer);

			vertexBuffer->setLayout();
		}
	public:
		VertexArray3D()
			: ID(0)
		{
#if not defined(GLES20)
			GLCall(glGenVertexArrays(1, &ID));
#endif
		}
		VertexArray3D(VBO& vB, IndexBuffer3D& iB)
			: indexBuffer(&iB), vertexBuffer(&vB), ID(0)
		{
			setBuffers();
		}
		~VertexArray3D()
		{
#if not defined(GLES20)
			GLCall(glDeleteVertexArrays(1, &ID));
#endif
		}
		VBO& getVertexBuffer() const
		{
			return *vertexBuffer;
		}
		IndexBuffer3D& getIndexBuffer() const
		{
			return *indexBuffer;
		}
		void setBuffers(VBO& vB, IndexBuffer3D& iB)
		{
			vertexBuffer = &vB;
			indexBuffer = &iB;
			setBuffers();
		}
		void setVBO(VBO& vB)
		{
			vertexBuffer = &vB;
			indexBuffer = nullptr;
			setBuffers();
		}
		static void Bind(const VertexArray3D& vao)
		{
#if not defined(GLES20)
			GLCall(glBindVertexArray(vao.ID));
#else
			if (vao.vertexBuffer)
			{
				VBO::Bind(*vao.vertexBuffer);
			}
			if (vao.indexBuffer)
			{
				IndexBuffer3D::Bind(*vao.indexBuffer);
			}
#endif
		}

	};
}