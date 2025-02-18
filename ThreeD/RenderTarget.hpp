#pragma once
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
        void clear3D(const ColorF color = ColorF(), std::uint32_t clearCall = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        void setView3D(const View3D& view);
        const View3D& getView3D() const;
        void setProjection3D(const Projection3D& proj);
        const Projection3D& getProjection3D() const;
        void draw3D(const Drawable3D& drawable, const RenderStates3D& states = RenderStates3D::Default);
        template<typename T>
        void draw3D(const VertexArray3D<T>* vao, sf::PrimitiveType type = sf::PrimitiveType::Points, const RenderStates3D& states = RenderStates3D::Default);

    protected:
        RenderTarget3D();
    private:
        View3D view; 
        Projection3D proj;
   };
}

#include "RenderTarget.inl"