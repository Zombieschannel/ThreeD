#include "VertexArray.hpp"

namespace DDD
{
    template <typename T>
    VertexArray3D<T>::VertexArray3D()
		: ID(0)
	{
#ifndef GLES20
		GLCall(glGenVertexArrays(1, &ID));
#endif
	}

    template <typename T>
    VertexArray3D<T>::VertexArray3D(const VertexBuffer3D<T>* vertexBuffer, const IndexBuffer3D* indexBuffer)
		: indexBuffer(indexBuffer), vertexBuffer(vertexBuffer)
	{
#ifndef GLES20
		GLCall(glGenVertexArrays(1, &ID));
#endif
	}

    template <typename T>
    VertexArray3D<T>::~VertexArray3D()
	{
#ifndef GLES20
		GLCall(glDeleteVertexArrays(1, &ID));
#endif
	}

    template <typename T>
    std::uint32_t VertexArray3D<T>::getHandle() const
    {
        return ID;
    }

    template <typename T>
    const VertexBuffer3D<T>* VertexArray3D<T>::getVertexBuffer() const
	{
		return vertexBuffer;
	}

    template <typename T>
    const IndexBuffer3D* VertexArray3D<T>::getIndexBuffer() const
	{
		return indexBuffer;
	}

    template <typename T>
    void VertexArray3D<T>::setBuffers(const VertexBuffer3D<T>* vertexBuffer, const IndexBuffer3D* indexBuffer)
	{
		this->vertexBuffer = vertexBuffer;
		this->indexBuffer = indexBuffer;
	}

    template <typename T>
    void VertexArray3D<T>::setLayout(const std::vector<std::uint32_t>& attribLocation)
    {
		if (vertexBuffer)
			vertexBuffer->setLayout(attribLocation);
    }

    template <typename T>
    void VertexArray3D<T>::UpdateVertexBuffer()
    {
		if (vertexBuffer)
			vertexBuffer->Update();
    }

    template <typename T>
    void VertexArray3D<T>::UpdateIndexBuffer()
    {
		if (indexBuffer)
			indexBuffer->Update();
    }
    
    template <typename T>
    void BindVertexArray(const VertexArray3D<T>* vao)
    {
		if (vao)
		{
#ifndef GLES20
			GLCall(glBindVertexArray(vao->ID));
#else
			if (vao->vertexBuffer)
				BindVertexBuffer(vao->vertexBuffer);
			if (vao->indexBuffer)
				BindIndexBuffer(*vao->indexBuffer);
#endif
		}
		else
		{
#ifndef GLES20
			GLCall(glBindVertexArray(0));
#else
			BindVertexBuffer(0);
			BindIndexBuffer(0);
#endif
		}
	}
}