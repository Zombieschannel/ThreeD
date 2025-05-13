#pragma once
#include "Transformable.hpp"
#include "VertexArray.hpp"

namespace DDD
{
    class Shape3D : public Transformable3D
    {
    public:
        virtual ~Shape3D() = default;
        void setFillColor(const ColorF& color, int index);
        void setFillColor(const ColorF& color);
        const ColorF& getFillColor(unsigned int index) const;
        virtual unsigned int getPointCount() const = 0;
        virtual sf::Vector3f getPoint(std::uint32_t index) const = 0;
    protected:
        Shape3D() = default;
        virtual void update() const = 0;
        std::vector<ColorF> fillColors;
        mutable VertexBuffer3D<Vertex3D> vbo;
        mutable IndexBuffer3D ibo;
        mutable bool needUpdate = false;
    };
}
