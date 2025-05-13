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
        ~Cube3D() = default;
        void setSize(const sf::Vector3f size);
        const sf::Vector3f getSize() const;
        unsigned int getPointCount() const override;
        sf::Vector3f getPoint(std::uint32_t index) const override;
    
    private:
        void draw(RenderTarget3D& target, RenderStates3D states) const override;
        void update() const override;
    
        sf::Vector3f size;
    };
}