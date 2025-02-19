#pragma once
#include <SFML/Graphics/BlendMode.hpp>
#include "Drawable.hpp"
#include "View.hpp"
#include "Projection.hpp"
#include "VertexArray.hpp"

namespace DDD
{
    class RenderTarget3D
    {
    public:
        virtual ~RenderTarget3D();
        RenderTarget3D(const RenderTarget3D&) = delete;

        void clear(const ColorF color = ColorF());
        void setView(const View3D& view);
        const View3D& getView() const;
        void setProjection(const Projection3D& proj);
        const Projection3D& getProjection() const;
        virtual sf::Vector2u getSize() const = 0;

        void draw(const Drawable3D& drawable, const RenderStates3D& states = RenderStates3D::Default);
        template<typename T>
        void draw(const VertexArray3D<T>* vao, sf::PrimitiveType type = sf::PrimitiveType::Points, const RenderStates3D& states = RenderStates3D::Default);
        template<typename T>
        void draw(const VertexBuffer3D<T>* vbo, const IndexBuffer3D* ibo, sf::PrimitiveType type = sf::PrimitiveType::Points, const RenderStates3D& states = RenderStates3D::Default);

    protected:
        RenderTarget3D();
        void initialize();
    private:
        std::uint32_t blendFactorToGLtype(const sf::BlendMode::Factor factor);
        std::uint32_t blendEquationToGLtype(const sf::BlendMode::Equation equation);
        std::uint32_t primitiveTypeToGLtype(const sf::PrimitiveType equation);
        std::uint32_t componentToGLtype(const DDD::Component component);
        std::uint8_t componentToGLsize(const DDD::Component component);
        View3D view; 
        Projection3D proj;
        bool initialized = false;
   };
}

#include "RenderTarget.inl"