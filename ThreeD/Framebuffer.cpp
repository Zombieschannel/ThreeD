#include "Framebuffer.hpp"

namespace DDD
{
    FrameBuffer3D::FrameBuffer3D()
    {
        GLCall(glGenFramebuffers(1, &ID));
    }
    FrameBuffer3D::~FrameBuffer3D()
    {
        GLCall(glDeleteFramebuffers(1, &ID));
    }
    std::uint32_t FrameBuffer3D::getHandle() const
    {
        return ID;
    }
    void FrameBuffer3D::attachTexture(const Texture3D &texture, Type type)
    {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<std::uint32_t>(type), GL_TEXTURE_2D, texture.ID, 0));
        size = texture.getSize();
        texture.flipped = 1;
        initialize();
    }
    void FrameBuffer3D::attachRenderBuffer(const RenderBuffer3D &renderbuffer, Type type)
    {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
        GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<std::uint32_t>(type), GL_RENDERBUFFER, renderbuffer.ID));
        size = renderbuffer.getSize();
        initialize();
    }
    sf::Vector2u FrameBuffer3D::getSize() const
    {
        return size;
    }
    void BindFrameBuffer(const FrameBuffer3D *framebuffer)
    {
        if (framebuffer)
        {
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->getHandle()));
        }
        else
        {
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        }
    }
}