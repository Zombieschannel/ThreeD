#pragma once
#include "Transformable.h"
#include "VertexArray.h"

namespace DDD
{
    class Shape3D : public Transformable3D
    {
    public:
        virtual ~Shape3D()
        {

        }
        //void setTexture(const Texture* texture, bool resetRect = false)
        //{

        //}

        //void setTextureRect(const IntRect& rect);

        void setFillColor(const ColorF& color, int index)
        {
            fillColor[index] = color;
            vbo[index].setColor(fillColor[index]);
            vao.setBuffers(vbo, ibo);
        }
        void setFillColor(const ColorF& color)
        {
            for (int i = 0; i < getPointCount(); i++)
                fillColor[i] = color;
            for (int i = 0; i < vbo.getVertexCount(); i++)
                vbo[i].setColor(fillColor[i]);
            vao.setBuffers(vbo, ibo);
        }

        /*void setOutlineColor(const Color& color);

        void setOutlineThickness(float thickness);

        

        const IntRect& getTextureRect() const;*/

        const ColorF& getFillColor(unsigned int index) const
        {
            return fillColor[index];
        }

       /* const Color& getOutlineColor() const;

        float getOutlineThickness() const;*/

        virtual unsigned int getPointCount() const = 0;

        virtual sf::Vector3f getPoint(std::size_t index) const = 0;

        //FloatRect getLocalBounds() const;

        //FloatRect getGlobalBounds() const;

    protected:
        Shape3D()
        {

        }
        virtual void update()
        {
            
        }
        void updateFillColors()
        {
            for (int i = 0; i < vbo.getVertexCount(); i++)
                vbo[i].setColor(fillColor[i]);
            vao.setBuffers(vbo, ibo);
        }
        std::vector<ColorF> fillColor;
        VertexBuffer3D vbo;
        IndexBuffer3D ibo;
        VertexArray3D vao;


    };
}