#pragma once
#include "Transformable.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace DDD
{
    class Shape3D : public Transformable3D, public sf::GlResource
    {
    public:
        ~Shape3D() override = default;
        void setFillColor(const ColorF& color, int index);
        void setFillColor(const ColorF& color);
        const ColorF& getFillColor(std::uint32_t index) const;
        virtual std::uint32_t getPointCount() const = 0;
        virtual sf::Vector3f getPoint(std::uint32_t index) const = 0;
    protected:
        Shape3D() = default;
        std::vector<ColorF> fillColors;
        mutable VertexBuffer3D<Vertex3D> vbo;
        mutable IndexBuffer3D ibo;
        mutable bool needUpdate = false;
    };
}
