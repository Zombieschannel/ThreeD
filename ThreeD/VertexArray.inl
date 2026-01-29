#include <SFML/Window/Context.hpp>
#include "VertexArray.hpp"
#include "glad/glad.h"
namespace DDD
{
    template <typename T>
    VertexArray3D<T>::VertexArray3D()
		: m_array(0)
	{
    	const TransientContextLock lock;

		GLCall(glGenVertexArrays(1, &m_array));
	}

    template <typename T>
    VertexArray3D<T>::VertexArray3D(const VertexBuffer3D<T>* vertexBuffer, const IndexBuffer3D* indexBuffer)
		: indexBuffer(indexBuffer), vertexBuffer(vertexBuffer)
	{
		GLCall(glGenVertexArrays(1, &m_array));
	}

    template <typename T>
    VertexArray3D<T>::~VertexArray3D()
	{
		GLCall(glDeleteVertexArrays(1, &m_array));
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
			GLCall(glBindVertexArray(vao->getHandle()));
		}
		else
		{
			GLCall(glBindVertexArray(0));
		}
	}
}