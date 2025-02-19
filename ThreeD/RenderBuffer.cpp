#include "RenderBuffer.hpp"
#include "Error.hpp"

namespace DDD
{
    RenderBuffer3D::RenderBuffer3D()
    {
        GLCall(glGenRenderbuffers(1, &ID));
    }
    RenderBuffer3D::~RenderBuffer3D()
    {
        GLCall(glDeleteRenderbuffers(1, &ID));
    }
    std::uint32_t RenderBuffer3D::getHandle() const
    {
        return ID;
    }
    void RenderBuffer3D::create(const sf::Vector2u size, const std::uint32_t internalFormat)
    {
        GLCall(glBindRenderbuffer(GL_RENDERBUFFER, ID));
        GLCall(glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, size.x, size.y));
        this->size = size;
    }
    const sf::Vector2u RenderBuffer3D::getSize() const
    {
        return size;
    }
}