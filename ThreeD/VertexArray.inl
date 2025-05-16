#include "VertexArray.hpp"

namespace DDD
{
    template <typename T>
    VertexArray3D<T>::VertexArray3D()
		: m_array(0)
	{
#ifndef GLES20
		GLCall(glGenVertexArrays(1, &m_array));
#endif
	}

    template <typename T>
    VertexArray3D<T>::VertexArray3D(const VertexBuffer3D<T>* vertexBuffer, const IndexBuffer3D* indexBuffer)
		: indexBuffer(indexBuffer), vertexBuffer(vertexBuffer)
	{
#ifndef GLES20
		GLCall(glGenVertexArrays(1, &m_array));
#endif
	}

    template <typename T>
    VertexArray3D<T>::~VertexArray3D()
	{
#ifndef GLES20
		GLCall(glDeleteVertexArrays(1, &m_array));
#endif
	}

    template <typename T>
    std::uint32_t VertexArray3D<T>::getHandle() const
    {
        return m_array;
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
    void VertexArray3D<T>::UpdateVertexBuffer() const
    {
		if (vertexBuffer)
			vertexBuffer->update();
    }

    template <typename T>
    void VertexArray3D<T>::UpdateIndexBuffer() const
    {
		if (indexBuffer)
			indexBuffer->update();
    }
    
    template <typename T>
    void BindVertexArray(const VertexArray3D<T>* vao)
    {
		if (vao)
		{
#ifndef GLES20
			GLCall(glBindVertexArray(vao->getHandle()));
#else
	        if (vao->getVertexBuffer())
	            BindVertexBuffer(vao->getVertexBuffer());
	        if (vao->getIndexBuffer())
	            BindIndexBuffer(vao->getIndexBuffer());
#endif
		}
		else
		{
#ifndef GLES20
			GLCall(glBindVertexArray(0));
#else
			BindVertexBuffer<char>(nullptr);
			BindIndexBuffer(0);
#endif
		}
	}
}