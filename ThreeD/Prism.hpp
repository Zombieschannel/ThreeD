#pragma once
#include "Shape.hpp"
#include "Drawable.hpp"
#include "RenderTarget.hpp"

namespace DDD
{
    class Prism3D : public Shape3D, public Drawable3D
    {
    public:
        Prism3D(float radius = 0, float depth = 0, std::uint32_t pointCount = 20);
        ~Prism3D() override = default;
        void setRadius(float radius);
        void setPointCount(std::uint32_t pointCount);
        void setHeight(float height);
        float getRadius() const;
        float getHeight() const;
        std::uint32_t getPointCount() const override;
        sf::Vector3f getPoint(std::uint32_t index) const override;
    private:
        void draw(RenderTarget3D& target, RenderStates3D states) const override;
        void appendQuad(std::uint32_t i0, std::uint32_t i1, std::uint32_t i2, std::uint32_t i3) const;
        virtual void update() const;

        float radius;
        std::uint32_t pointCount;
        float height;
    };
}