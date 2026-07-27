#include "Prism.hpp"

#include <cmath>

namespace DDD
{
    Prism3D::Prism3D(const float radius, const float depth, const std::uint32_t pointCount)
        : height(depth), radius(radius), pointCount(pointCount)
    {
        fillColors.resize(getPointCount() * 2, {1.f, 1.f, 1.f, 1.f});
        needUpdate = true;
    }
    void Prism3D::setRadius(const float radius)
    {
        if (radius == this->radius)
            return;
        this->radius = radius;
        needUpdate = true;
    }
    void Prism3D::setPointCount(const std::uint32_t pointCount)
    {
        if (pointCount == this->pointCount)
            return;
        this->pointCount = pointCount;
        fillColors.resize(getPointCount() * 2);
        needUpdate = true;
    }

    void Prism3D::setHeight(const float height)
    {
        if (height == this->height)
            return;
        this->height = height;
        needUpdate = true;
    }
    float Prism3D::getRadius() const
    {
        return radius;
    }
    float Prism3D::getHeight() const
    {
        return height;
    }
    std::uint32_t Prism3D::getPointCount() const
    {
        return pointCount + 1;
    }

    sf::Vector3f Prism3D::getPoint(std::uint32_t index) const
    {
        const float angleBetween = 360.f / (getPointCount() - 1);
        if (index == 0)
            return {0.f, 0.f, 0.f};
        if (index == getPointCount())
        {
            return {0.f, height, 0.f};
        }
        if (index > getPointCount())
        {
            index -= getPointCount();
            return {std::cosf((angleBetween * index) * 0.0174533f)
                                * radius, height, std::sin((angleBetween * index) * 0.0174533f) * radius};
        }
        return {std::cosf((angleBetween * index) * 0.0174533f)
                            * radius, 0.f, std::sin((angleBetween * index) * 0.0174533f) * radius};
    }
    void Prism3D::draw(RenderTarget3D& target, RenderStates3D states) const
    {
        if (needUpdate)
            update();
        states.transform *= getTransform();
        target.draw(&vbo, &ibo, sf::PrimitiveType::Triangles, states);
    }
    void Prism3D::appendQuad(const std::uint32_t i0, const std::uint32_t i1, const std::uint32_t i2, const std::uint32_t i3) const
    {
        ibo.append(i0);
        ibo.append(i1);
        ibo.append(i2);
        ibo.append(i0);
        ibo.append(i2);
        ibo.append(i3);
    }
    void Prism3D::update() const
    {
        const std::uint32_t count = getPointCount();
        if (count < 3)
        {
            vbo.resize(0);
            ibo.resize(0);
            vbo.update();
            ibo.update();
            return;
        }
        vbo.clear();
        vbo.resize(count * 2);
        for (std::uint32_t i = 0; i < count * 2; i++)
            vbo[i].position = getPoint(i);
        ibo.clear();
        for (std::uint32_t j = 0; j < count * 2; j += count)
        {
            for (std::uint32_t i = 1; i < count; i++)
            {
                ibo.append(j + 0);
                ibo.append(j + i);
                if (j + i + 1 < j + count)
                    ibo.append(j + i + 1);
                else
                    ibo.append(j + 1);
            }
        }
        for (std::uint32_t i = 1; i < count; i++)
        {
            if (i + 1 >= count)
            {
                appendQuad(i, i + count, count + 1, 1);
                continue;
            }
            appendQuad(i, i + count, i + count + 1, i + 1);
        }
        for (std::uint32_t i = 0; i < fillColors.size(); i++)
            vbo[i].color = fillColors[i];
        vbo.update();
        ibo.update();
        needUpdate = false;
    }
}