#include "Plane.hpp"

namespace DDD
{
    Plane3D::Plane3D(const sf::Vector2f size)
        :size(size), texRect({0, 0}, {0, 0})
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
    void Plane3D::setSize(const sf::Vector2f size)
    {
        this->size = size;
        for (int i = 0; i < getPointCount(); i++)
            vbo[i].position = getPoint(i);
        needUpdate = true;
    }
    void Plane3D::setTexture(const Texture3D* texture)
    {
        this->texture = texture;
    }
    const Texture3D* Plane3D::getTexture() const
    {
        return texture;
    }
    void Plane3D::setTextureRect(const sf::IntRect& texRect)
    {
        this->texRect = texRect;
    }
    const sf::IntRect& Plane3D::getTextureRect() const
    {
        return texRect;
    }
    sf::Vector2f Plane3D::getSize() const
    {
        return size;
    }
    std::uint32_t Plane3D::getPointCount() const
    {
        return 4;
    }
    sf::Vector3f Plane3D::getPoint(std::uint32_t index) const
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
    void Plane3D::draw(RenderTarget3D& target, RenderStates3D states) const
    {
        if (needUpdate)
            update();
        states.transform *= getTransform();
        states.texture = texture;
        target.draw(&vbo, &ibo, sf::PrimitiveType::TriangleFan, states);
    }
    void Plane3D::update() const
    {
        vbo.update();
        needUpdate = false;
    }
}