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
        ~Cube3D();
        void setSize(float x, float y, float z);
        void setSize(const sf::Vector3f& size);
        const sf::Vector3f& getSize() const;
        virtual unsigned int getPointCount() const;
        virtual sf::Vector3f getPoint(std::size_t index) const;
    
    private:
        virtual void draw(RenderTarget3D& target, RenderStates3D states) const;
        virtual void update();
    
        const Texture3D* texture = nullptr;
        std::vector<sf::FloatRect> coord;
        sf::Vector3f size;
    };
}