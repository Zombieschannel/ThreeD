#include "IndexBuffer.hpp"
#include "Error.hpp"
#include <GL/gl.h>
namespace
{
    std::uint32_t drawTypeToGLtype(DDD::DrawType type)
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
    IndexBuffer3D::IndexBuffer3D()
    {
        GLCall(glGenBuffers(1, &ID));
    }
    IndexBuffer3D::IndexBuffer3D(std::uint32_t vertexCount)
    {
        GLCall(glGenBuffers(1, &ID));
        indices.resize(vertexCount);
    }
    IndexBuffer3D::~IndexBuffer3D()
    {
        GLCall(glDeleteBuffers(1, &ID));
    }
    std::uint32_t IndexBuffer3D::getHandle() const
    {
        return ID;
    }
    std::uint32_t IndexBuffer3D::getIndexCount() const
    {
        return indices.size();
    }
    std::uint16_t& IndexBuffer3D::operator[](std::uint32_t index)
    {
        return indices[index];
    }
    const std::uint16_t& IndexBuffer3D::operator[](std::uint32_t index) const
    {
        return indices[index];
    }
    void IndexBuffer3D::clear()
    {
        indices.clear();
    }
    void IndexBuffer3D::resize(std::uint32_t indexCount)
    {
        indices.resize(indexCount);
    }
    void IndexBuffer3D::append(std::uint16_t index)
    {
        indices.push_back(index);
    }
    void IndexBuffer3D::replace(const std::vector<std::uint16_t>& indices)
    {
        this->indices = indices;
    }
    void IndexBuffer3D::setDrawType(DrawType type)
    {
        drawType = type;
    }
    DrawType IndexBuffer3D::getDrawType() const
    {
        return drawType;
    }
    void IndexBuffer3D::update() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint16_t), indices.data(), drawTypeToGLtype(drawType)));
    }
    void BindIndexBuffer(const IndexBuffer3D* buffer)
    {
        if (buffer)
        {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->getHandle()));
        }
        else
        {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }
    }
}