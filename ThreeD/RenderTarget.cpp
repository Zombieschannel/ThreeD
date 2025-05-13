#include "RenderTarget.hpp"

#ifndef GL_MIN
    #define GL_MIN 0
#endif

#ifndef GL_MAX
    #define GL_MAX 0
#endif

#ifndef GL_QUADS
#define GL_QUADS 0
#endif

namespace DDD
{
    void RenderTarget3D::clear(const ColorF color)
    {
        GLCall(glClearColor(color.r, color.g, color.b, color.a));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }
    void RenderTarget3D::clearDepth()
    {
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    }
    void RenderTarget3D::setDepthTestingEnabled(const bool state)
    {
        if (state)
        {
            GLCall(glEnable(GL_DEPTH_TEST));
        }
        else
        {
            GLCall(glDisable(GL_DEPTH_TEST));
        }
    }
    void RenderTarget3D::setView3D(const View3D& view)
    {
        this->m_view3D = view;
    }
    const View3D& RenderTarget3D::getView3D() const
    {
        return m_view3D;
    }
    void RenderTarget3D::setProjection3D(const Projection3D& proj)
    {
        this->m_proj3D = proj;
    }
    const Projection3D& RenderTarget3D::getProjection3D() const
    {
        return m_proj3D;
    }
    void RenderTarget3D::draw(const Drawable3D& drawable, const RenderStates3D& states)
    {
        drawable.draw(*this, states);
    }
    void RenderTarget3D::initialize()
    {
        m_proj3D.setViewport(sf::IntRect({ 0, 0 }, static_cast<sf::Vector2i>(getSize())));
        m_proj3D.setTransform(Transform3D::Perspective(75, static_cast<float>(getSize().x) / getSize().y, 1e-2, 1e6));
    }
    std::uint32_t RenderTarget3D::blendFactorToGLtype(const sf::BlendMode::Factor factor)
    {
        switch (factor)
        {
        case sf::BlendMode::Factor::Zero:             return GL_ZERO;
        case sf::BlendMode::Factor::One:              return GL_ONE;
        case sf::BlendMode::Factor::SrcColor:         return GL_SRC_COLOR;
        case sf::BlendMode::Factor::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
        case sf::BlendMode::Factor::DstColor:         return GL_DST_COLOR;
        case sf::BlendMode::Factor::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
        case sf::BlendMode::Factor::SrcAlpha:         return GL_SRC_ALPHA;
        case sf::BlendMode::Factor::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
        case sf::BlendMode::Factor::DstAlpha:         return GL_DST_ALPHA;
        case sf::BlendMode::Factor::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
        }
        return GL_ZERO;
    }
    std::uint32_t RenderTarget3D::blendEquationToGLtype(const sf::BlendMode::Equation equation)
    {
        switch (equation)
        {
        case sf::BlendMode::Equation::Add:               return GL_FUNC_ADD;
        case sf::BlendMode::Equation::Subtract:          return GL_FUNC_SUBTRACT;
        case sf::BlendMode::Equation::ReverseSubtract:   return GL_FUNC_REVERSE_SUBTRACT;
        case sf::BlendMode::Equation::Min:               return GL_MIN;
        case sf::BlendMode::Equation::Max:               return GL_MAX;
        }
        return GL_FUNC_ADD;
    }
    std::uint32_t RenderTarget3D::primitiveTypeToGLtype(const sf::PrimitiveType equation)
    {
        switch (equation)
        {
        case sf::PrimitiveType::Points:            return GL_POINTS;
        case sf::PrimitiveType::Lines:             return GL_LINES;
        case sf::PrimitiveType::LineStrip:         return GL_LINE_STRIP;
        case sf::PrimitiveType::Triangles:         return GL_TRIANGLES;
        case sf::PrimitiveType::TriangleStrip:     return GL_TRIANGLE_STRIP;
        case sf::PrimitiveType::TriangleFan:       return GL_TRIANGLE_FAN;
        }
        return GL_POINTS;
    }
    std::uint32_t RenderTarget3D::componentToGLtype(const DDD::Component component)
    {
        switch (component)
        {
        case DDD::Component::Byte: return GL_BYTE;
        case DDD::Component::UByte: return GL_UNSIGNED_BYTE;
        case DDD::Component::Short: return GL_SHORT;
        case DDD::Component::UShort: return GL_UNSIGNED_SHORT;
        case DDD::Component::Int: return GL_INT;
        case DDD::Component::UInt: return GL_UNSIGNED_INT;
        case DDD::Component::Float: return GL_FLOAT;
        }
    }
    std::uint8_t RenderTarget3D::componentToGLsize(const DDD::Component component)
    {
        switch (component)
        {
        case DDD::Component::Byte: return 1;
        case DDD::Component::UByte: return 1;
        case DDD::Component::Short: return 2;
        case DDD::Component::UShort: return 2;
        case DDD::Component::Int: return 4;
        case DDD::Component::UInt: return 4;
        case DDD::Component::Float: return 4;
        }
    }
}