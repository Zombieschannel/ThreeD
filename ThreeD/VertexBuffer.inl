#include "VertexBuffer.hpp"
#include "VertexComponent.hpp"

namespace
{
    std::uint32_t drawTypeToGLtype(const DDD::DrawType type)
    {
        switch (type)
        {
        case DDD::DrawType::Static:
            return GL_STATIC_DRAW;
        case DDD::DrawType::Dynamic:
            return GL_DYNAMIC_DRAW;
        case DDD::DrawType::Stream:
            return GL_STREAM_DRAW;
        }
        return GL_STATIC_DRAW;
    }
}

namespace DDD
{
    template <typename T>
    VertexBuffer3D<T>::VertexBuffer3D()
    {
        GLCall(glGenBuffers(1, &ID));
    }
    template <typename T>
    VertexBuffer3D<T>::~VertexBuffer3D()
    {
        GLCall(glDeleteBuffers(1, &ID));
    }
    template <typename T>
    std::uint32_t VertexBuffer3D<T>::getHandle() const
    {
        return ID;
    }
    template <typename T>
    const void *VertexBuffer3D<T>::getFirstVertex() const
    {
        return &vertices[0];
    }
    template <typename T>
    std::uint32_t VertexBuffer3D<T>::getVertexCount() const
    {
        return vertices.size();
    }
    template <typename T>
    std::uint32_t VertexBuffer3D<T>::getVertexSize() const
    {
        return sizeof(T);
    }
    template<typename T>
    const std::vector<std::uint8_t>& VertexBuffer3D<T>::getAttribLocation() const
    {
        return attribLocation;
    }
    template <typename T>
    T& VertexBuffer3D<T>::operator[](std::uint32_t index)
    {
        return vertices[index];
    }
    template <typename T>
    void VertexBuffer3D<T>::clear()
    {
        vertices.clear();
    }
    template <typename T>
    void VertexBuffer3D<T>::resize(const std::uint32_t vertexCount)
    {
        vertices.resize(vertexCount);
    }
    template <typename T>
    void VertexBuffer3D<T>::append(const T& vertex)
    {
        vertices.push_back(vertex);
    }
    template <typename T>
    void VertexBuffer3D<T>::setDrawType(const DrawType type)
    {
        drawType = type;
    }
    template <typename T>
    const T& VertexBuffer3D<T>::at(const std::uint32_t index) const
    {
        return vertices.at(index);
    }
    template <typename T>
    DrawType VertexBuffer3D<T>::getDrawType() const
    {
        return drawType;
    }
    template <typename T>
    void VertexBuffer3D<T>::setAttribLocation(const std::vector<std::uint8_t>& attribLocation)
    {
        this->attribLocation = attribLocation;
    }
    template <typename T>
    void VertexBuffer3D<T>::update() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, getVertexCount() * getVertexSize(), getFirstVertex(), drawTypeToGLtype(drawType)));
    }
    template <typename T>
    void BindVertexBuffer(const VertexBuffer3D<T>* buffer)
    {
        if (buffer)
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer->getHandle()));
        }
        else
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }
    }
}