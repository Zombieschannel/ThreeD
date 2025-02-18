#include "Cube.hpp"

namespace DDD
{
    Cube3D::Cube3D()
    {
        fillColor.resize(getPointCount(), {1.f, 1.f, 1.f, 1.f}});
        coord.resize(6);
        update();
    }
    Cube3D::~Cube3D()
    {
    }
    void Cube3D::setSize(float x, float y, float z)
    {
        this->size = sf::Vector3f(x, y, z);
        update();
    }
    void Cube3D::setSize(const sf::Vector3f &size)
    {
        this->size = size;
        update();
    }
    const Cube3D::sf::Vector3f &getSize() const
    {
        return size;
    }
    unsigned int Cube3D::getPointCount() const
    {
        return 8;
    }
    sf::Vector3f Cube3D::getPoint(std::size_t index) const
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
    void draw(RenderTarget3D& target, RenderStates3D states) const
    {
        states.transform *= getTransform();
        states.texture = texture;
        target.draw3D(&vao, sf::PrimitiveType::Triangles, states);
    }
    void Cube3D::update()
    {
        int count = getPointCount();
        if (count < 3)
        {
            vbo.resize(0);
            return;
        }
        vbo.resize(getPointCount());
        for (int i = 0; i < getPointCount(); i++)
            vbo[i].setPosition(getPoint(i));
        ibo.replace(std::vector<unsigned int>() = {
            0, 1, 2, 2, 3, 0,
            0, 4, 7, 7, 3, 0,
            5, 1, 2, 2, 6, 5,
            0, 1, 5, 5, 4, 0,
            7, 6, 2, 2, 3, 7,
            4, 5, 6, 6, 7, 4,
        });
        
        updateFillColors();
    }
}