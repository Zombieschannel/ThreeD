#include "Cube.hpp"

namespace DDD
{
    Cube3D::Cube3D()
    {
        fillColors.resize(getPointCount(), {1.f, 1.f, 1.f, 1.f});
        vbo.resize(getPointCount());
        ibo.replace(std::vector<std::uint16_t>() = {
            0, 1, 2, 2, 3, 0,
            0, 4, 7, 7, 3, 0,
            5, 1, 2, 2, 6, 5,
            0, 1, 5, 5, 4, 0,
            7, 6, 2, 2, 3, 7,
            4, 5, 6, 6, 7, 4,
        });
        ibo.update();
        needUpdate = true;
    }
    void Cube3D::setSize(const sf::Vector3f size)
    {
        this->size = size;
        for (int i = 0; i < getPointCount(); i++)
            vbo[i].position = getPoint(i);
        needUpdate = true;
    }
    const sf::Vector3f Cube3D::getSize() const
    {
        return size;
    }
    std::uint32_t Cube3D::getPointCount() const
    {
        return 8;
    }
    sf::Vector3f Cube3D::getPoint(std::uint32_t index) const
    {
        switch (index)
        {
        default:
        case 0: return sf::Vector3f(0, 0, 0);
        case 1: return sf::Vector3f(size.x, 0, 0);
        case 2: return sf::Vector3f(size.x, size.y, 0);
        case 3: return sf::Vector3f(0, size.y, 0);
        case 4: return sf::Vector3f(0, 0, size.z);
        case 5: return sf::Vector3f(size.x, 0, size.z);
        case 6: return sf::Vector3f(size.x, size.y, size.z);
        case 7: return sf::Vector3f(0, size.y, size.z);
        }
    }
    void Cube3D::draw(RenderTarget3D& target, RenderStates3D states) const
    {
        if (needUpdate)
            update();
        states.transform *= getTransform();
        target.draw(&vbo, &ibo, sf::PrimitiveType::Triangles, states);
    }
    void Cube3D::update() const
    {
        vbo.update();
        needUpdate = false;
    }
}