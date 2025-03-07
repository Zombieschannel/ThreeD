#include "IndexBuffer.hpp"
#include "Error.hpp"

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
    void IndexBuffer3D::setDrawType(DrawType type)
    {
        drawType = type;
    }
    DrawType IndexBuffer3D::getDrawType() const
    {
        return drawType;
    }
    void IndexBuffer3D::Update() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint16_t), indices.data(), static_cast<std::uint32_t>(drawType)));
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