#pragma once
#include "Shape.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"
#include "RenderTarget.hpp"

namespace DDD
{
    class Plane3D : public Shape3D, public Drawable3D
    {
    public:
        Plane3D(sf::Vector2f size = sf::Vector2f(0, 0));
        void setSize(sf::Vector2f size);
        void setTexture(const Texture3D* texture);
        const Texture3D* getTexture() const;
        void setTextureRect(const sf::IntRect& texRect);
        const sf::IntRect& getTextureRect() const;
        sf::Vector2f getSize() const;
        std::uint32_t getPointCount() const override;
        sf::Vector3f getPoint(std::uint32_t index) const override;
    private:
        void draw(RenderTarget3D& target, RenderStates3D states) const override;
        void update() const;
        const Texture3D* texture = nullptr;
        sf::IntRect texRect;
        sf::Vector2f size;
    };
}