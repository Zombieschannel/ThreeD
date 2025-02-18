#include "Vertex.hpp"

namespace DDD
{
    Vertex3D::Vertex3D()
        : position{ 0, 0, 0 }, color{ 1, 1, 1, 1 }, texCoord{ 0, 0 }
    {
    }
    Vertex3D::Vertex3D(const sf::Vector3f pos)
        : position{ pos.x, pos.y, pos.z }, color{ 1, 1, 1, 1 }, texCoord{ 0, 0 }
    {
    }
    Vertex3D::Vertex3D(const sf::Vector3f pos, const ColorF col)
        : position{ pos.x, pos.y, pos.z }, color{ col.r, col.g, col.b, col.a }, texCoord{ 0, 0 }
    {

    }
    Vertex3D::Vertex3D(const sf::Vector3f pos, const ColorF col, const sf::Vector2f tex)
        : position{ pos.x, pos.y, pos.z }, color{ col.r, col.g, col.b, col.a }, texCoord{ tex.x, tex.y }
    {

    }
    Vertex3D::~Vertex3D()
    {
    }
    std::uint8_t Vertex3D::componentSize(const std::uint8_t component)
    {
        switch (component)
        {
        case 0: return sizeof(sf::Vector3f);
        case 1: return sizeof(ColorF);
        case 2: return sizeof(sf::Vector2f);
        default: return 0;
        }
    }
    Component Vertex3D::componentType(const std::uint8_t component)
    {
        return Component::Float;
    }
}