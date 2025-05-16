#pragma once
#include "Shape.hpp"
#include "Drawable.hpp"
#include "RenderTarget.hpp"

namespace DDD
{
    class Cube3D : public Shape3D, public Drawable3D
    {
    public:
        Cube3D();
        ~Cube3D() override = default;
        void setSize(sf::Vector3f size);
        sf::Vector3f getSize() const;
        std::uint32_t getPointCount() const override;
        sf::Vector3f getPoint(std::uint32_t index) const override;
    
    private:
        void draw(RenderTarget3D& target, RenderStates3D states) const override;
        void update() const;
    
        sf::Vector3f size;
    };
}