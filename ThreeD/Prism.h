#pragma once
#include "Shape.h"
#include "Drawable.h"
#include "RenderTarget.h"
namespace DDD
{
    class Prism3D : public Shape3D, public Drawable3D
    {
    public:
        Prism3D(float radius = 0, float depth = 0, unsigned int pointCount = 20)
            : depth(depth), radius(radius), pointCount(pointCount)
        {
            fillColor.resize(getPointCount() * 2, sf::Color(255, 255, 255));

            update();
        }
        ~Prism3D()
        {

        }
        void setRadius(float radius)
        {
            if (radius != this->radius)
            {
                this->radius = radius;
                UpdateRadius();
            }
        }
        void setPointCount(unsigned int pointCount)
        {
            if (pointCount != this->pointCount)
            {
                this->pointCount = pointCount;
               
                update();
            }
        }

        void setDepth(float depth)
        {
            if (depth != this->depth)
            {
                this->depth = depth;
                UpdateDepth();
            }
        }
        float getRadius() const 
        {
            return radius;
        }
        float getDepth() const
        {
            return depth;
        }
        virtual unsigned int getPointCount() const
        {
            return pointCount + 1;
        }

        virtual sf::Vector3f getPoint(unsigned int index) const
        {
            float angleBetween = 360.0 / (getPointCount() - 1);
            if (index == 0)
                return sf::Vector3f(0, 0, 0);
            else if (index == getPointCount())
            {
                return sf::Vector3f(0, depth, 0);
            }
            else if (index > getPointCount())
            {
                index -= getPointCount();
                return sf::Vector3f(cos((angleBetween * index) * 0.0174533f)
                    * radius, depth, sin((angleBetween * index) * 0.0174533f) * radius);
            }
            else
            {
                return sf::Vector3f(cos((angleBetween * index) * 0.0174533f)
                * radius, 0, sin((angleBetween * index) * 0.0174533f) * radius);
            }
        }
    private:
        virtual void draw(RenderTarget3D& target, RenderStates3D states) const
        {
            states.transform *= getTransform();
            target.draw3D(&vao, Triangles, states);
        }
        void appendQuad(unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3)
        {
            ibo.append(i0);
            ibo.append(i1);
            ibo.append(i2);
            ibo.append(i0);
            ibo.append(i2);
            ibo.append(i3);
        }
        virtual void update()
        {
            int count = getPointCount();
            if (count < 3)
            {
                vbo.resize(0);
                return;
            }
            fillColor.resize(getPointCount() * 2, sf::Color(255, 255, 255));
            vbo.clear();
            vbo.resize(getPointCount() * 2);
            for (int i = 0; i < getPointCount() * 2; i++)
            {
                vbo[i].setPosition(getPoint(i));
            }
            ibo.clear();
            for (int j = 0; j < getPointCount() * 2; j += getPointCount())
            {
                for (int i = 1; i < getPointCount(); i++)
                {
                    ibo.append(j + 0);
                    ibo.append(j + i);
                    if (j + i + 1 < j + getPointCount())
                        ibo.append(j + i + 1);
                    else
                        ibo.append(j + 1);
                }
            }
            for (int i = 1; i < getPointCount(); i++)
            {
                if (i + 1 >= getPointCount())
                {
                    appendQuad(i, i + getPointCount(), getPointCount() + 1, 1);
                    continue;
                }
                appendQuad(i, i + getPointCount(), i + getPointCount() + 1, i + 1);
            }



            updateFillColors();
        }
        void UpdateRadius()
        {
            for (int i = 0; i < getPointCount() * 2; i++)
            {
                vbo[i].setPosition(getPoint(i));
            }
            vao.setBuffers(vbo, ibo);
        }
        void UpdateDepth()
        {
            for (int i = getPointCount(); i < getPointCount() * 2; i++)
            {
                vbo[i].setPosition(getPoint(i));
            }
            vao.setBuffers(vbo, ibo);
        }
        float radius;
        unsigned int pointCount;
        float depth;
    };
}