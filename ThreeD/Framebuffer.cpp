#include "Framebuffer.hpp"

namespace DDD
{
    FrameBuffer3D::~FrameBuffer3D()
    {
        GLCall(glDeleteFramebuffers(1, &ID));
    }
    void FrameBuffer3D::create()
    {
        if (ID)
        {
            GLCall(glDeleteFramebuffers(1, &ID));
        }
        GLCall(glGenFramebuffers(1, &ID));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
    }
    void FrameBuffer3D::attachTexture(const Texture3D &texture, Type type)
    {
        if (!ID)
            return;
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<std::uint32_t>(type), GL_TEXTURE_2D, texture.ID, 0));
        texture.flipped = 1;
    }
    void FrameBuffer3D::attachRenderBuffer(const RenderBuffer3D &renderbuffer, Type type)
    {
        if (!ID)
            return;
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, ID));
        GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<std::uint32_t>(type), GL_RENDERBUFFER, renderbuffer.ID));
    }
    void FrameBuffer3D::Bind(const FrameBuffer3D *framebuffer)
    {
        if (framebuffer)
        {
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->ID));
        }
        else
        {
            GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        }
    }
}