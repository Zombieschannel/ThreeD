#include "Shape.hpp"

namespace DDD
{
    void Shape3D::setFillColor(const ColorF& color, int index)
    {
        if (fillColors.size() == vbo.getVertexCount())
            vbo[index].color = color;
        fillColors[index] = color;
        needUpdate = true;
    }
    void Shape3D::setFillColor(const ColorF& color)
    {
        for (auto& fillColor : fillColors)
            fillColor = color;
        for (std::uint32_t i = 0; i < vbo.getVertexCount(); i++)
            vbo[i].color = color;
        needUpdate = true;
    }
    const ColorF& Shape3D::getFillColor(const std::uint32_t index) const
    {
        return fillColors.at(index);
    }
}