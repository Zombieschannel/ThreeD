#include "RenderBuffer.hpp"
#include "Error.hpp"

namespace DDD
{
    RenderBuffer3D::RenderBuffer3D()
        : ID(0U)
    {

    }
    RenderBuffer3D::~RenderBuffer3D()
    {
        GLCall(glDeleteRenderbuffers(1, &ID));
    }
    void RenderBuffer3D::create(const sf::Vector2u size, const std::uint32_t internalFormat)
    {
        if (ID)
        {
            GLCall(glDeleteRenderbuffers(1, &ID));
        }
        GLCall(glGenRenderbuffers(1, &ID));
        GLCall(glBindRenderbuffer(GL_RENDERBUFFER, ID));
        GLCall(glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, size.x, size.y));
    }
}