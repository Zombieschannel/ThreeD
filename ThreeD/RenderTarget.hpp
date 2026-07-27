#pragma once
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/GlResource.hpp>
#include "Drawable.hpp"
#include "View.hpp"
#include "Projection.hpp"
#include "ColorF.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace DDD
{
    class RenderTarget3D : public sf::GlResource
    {
        struct ShaderCache
        {
            std::int8_t defPos = -1;
            std::int8_t defCol = -1;
            std::int8_t texPos = -1;
            std::int8_t texCol = -1;
            std::int8_t texTex = -1;
        };
    public:

        virtual ~RenderTarget3D();
        RenderTarget3D(const RenderTarget3D&) = delete;

        void clearColorF(ColorF color = ColorF());
        void clearDepth();
        void setDepthTestingEnabled(bool state);
        void setView3D(const View3D& view);
        const View3D& getView3D() const;
        void setProjection3D(const Projection3D& proj);
        const Projection3D& getProjection3D() const;
        virtual sf::Vector2u getSize() const = 0;

        void draw(const Drawable3D& drawable, const RenderStates3D& states = RenderStates3D::Default);
        template<typename T>
        void draw(const VertexBuffer3D<T>* vbo, const IndexBuffer3D* ibo, sf::PrimitiveType type = sf::PrimitiveType::Points, const RenderStates3D& states = RenderStates3D::Default);
        template<typename T>
        void draw(const VertexBuffer3D<T>* vbo, const IndexBuffer3D* ibo, std::uint32_t count, sf::PrimitiveType type = sf::PrimitiveType::Points, const RenderStates3D& states = RenderStates3D::Default);

    protected:
        RenderTarget3D() = default;
        void initialize();
    private:
        std::uint32_t blendFactorToGLtype(sf::BlendMode::Factor factor);
        std::uint32_t blendEquationToGLtype(sf::BlendMode::Equation equation);
        std::uint32_t primitiveTypeToGLtype(sf::PrimitiveType equation);
        std::uint32_t componentToGLtype(DDD::Component component);
        std::uint8_t componentToGLsize(DDD::Component component);

        View3D m_view3D;
        Projection3D m_proj3D;
        ShaderCache m_shaderCache;
        std::uint32_t m_defaultVAO = 0;
   };
}

#include "RenderTarget.inl"