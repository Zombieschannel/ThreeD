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
        Plane3D(const sf::Vector2f& Size = sf::Vector2f(0, 0))
            :size(Size), texRect({0, 0}, {0, 0})
        {
            fillColors.resize(getPointCount(), {1, 1, 1, 1});
            vbo.resize(getPointCount());
            vbo[0].texCoord = sf::Vector2f(0, 0);
            vbo[1].texCoord = sf::Vector2f(1, 0);
            vbo[2].texCoord = sf::Vector2f(1, 1);
            vbo[3].texCoord = sf::Vector2f(0, 1);
            ibo.replace(std::vector<std::uint16_t>() = { 0, 1, 2, 3 });
            ibo.update();
            needUpdate = true;
        }
        void setSize(const sf::Vector2f size)
        {
            this->size = size;
            for (int i = 0; i < getPointCount(); i++)
                vbo[i].position = getPoint(i);
            needUpdate = true;
        }
        void setTexture(const Texture3D* texture)
        {
            this->texture = texture;
        }
        const Texture3D* getTexture() const
        {
            return texture;
        }

        void setTextureRect(const sf::IntRect& texRect)
        {
            this->texRect = texRect;
        }
        const sf::IntRect& getTextureRect() const
        {
            return texRect;
        }

        const sf::Vector2f& getSize() const
        {
            return size;
        }

        virtual unsigned int getPointCount() const
        {
            return 4;
        }

        virtual sf::Vector3f getPoint(std::uint32_t index) const
        {
            switch (index)
            {
            default:
            case 0: return sf::Vector3f(0, 0, 0);
            case 1: return sf::Vector3f(size.x, 0, 0);
            case 2: return sf::Vector3f(size.x, size.y, 0);
            case 3: return sf::Vector3f(0, size.y, 0);
            }
        }
    private:
        void draw(RenderTarget3D& target, RenderStates3D states) const override
        {
            if (needUpdate)
                update();
            states.transform *= getTransform();
            states.texture = texture;
            target.draw(&vbo, &ibo, sf::PrimitiveType::TriangleFan, states);
        }
        void update() const override
        {
            vbo.update();
            needUpdate = false;
        }
        const Texture3D* texture = nullptr;
        sf::IntRect texRect;
        sf::Vector2f size;
    };
}