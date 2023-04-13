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
        static sf::Vector3f CalculateNormal(sf::Vector3f vec1, sf::Vector3f vec2, sf::Vector3f vec3)
        {
            sf::Vector3f A = vec2 - vec1;
            sf::Vector3f B = vec3 - vec1;
            sf::Vector3f N;
            N.x = A.y * B.z - A.z * B.y;
            N.y = A.z * B.x - A.x * B.z;
            N.z = A.x * B.y - A.y * B.x;
            return N;
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