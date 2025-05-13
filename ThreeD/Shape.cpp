#include "Shape.hpp"

namespace DDD
{
    void Shape3D::setFillColor(const ColorF& color, int index)
    {
        vbo[index].color = color;
        fillColors[index] = color;
        needUpdate = true;
    }
    void Shape3D::setFillColor(const ColorF& color)
    {
        for (int i = 0; i < vbo.getVertexCount(); i++)
        {
            vbo[i].color = color;
            fillColors[i] = color;
        }
        needUpdate = true;
    }
    const ColorF& Shape3D::getFillColor(std::uint32_t index) const
    {
        return vbo.at(index).color;
    }
}