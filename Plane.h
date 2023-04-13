#pragma once
#include "Shape.h"
#include "Texture.h"
#include "PrimitiveType.h"
#include "Drawable.h"
#include "RenderTarget.h"
namespace DDD
{
    class Plane3D : public Shape3D, public Drawable3D
    {
    public:
        Plane3D(const sf::Vector2f& Size = sf::Vector2f(0, 0))
            :size(Size), texRect(0, 0, 0, 0), normal(0, 0, 0)
        {
            fillColor.resize(getPointCount(), sf::Color(255, 255, 255));
            vbo.resize(getPointCount());

            ibo.replace(std::vector<unsigned int>() = {
                0, 1, 2, 2, 3, 0,
                });
            vao.setBuffers(vbo, ibo);
        }
        void setSize(float x, float y)
        {
            this->size = sf::Vector2f(x, y);
            int count = getPointCount();
            if (count < 3)
            {
                vbo.resize(0);
                return;
            }

            for (int i = 0; i < getPointCount(); i++)
                vbo[i].setPosition(getPoint(i));
            vao.setBuffers(vbo, ibo);
        }
        void setSize(const sf::Vector2f& size)
        {
            setSize(size.x, size.y);
        }
        void setTexture(const Texture3D& texture)
        {
            this->texture = &texture;
            //updateTexture();
        }
        const Texture3D& getTexture() const
        {
            return *texture;
        }

        void setTextureRect(const sf::IntRect& texRect)
        {
            this->texRect = texRect;
            updateTexture();
        }
        void setNormal(const sf::Vector3f& normal)
        {
            this->normal = normal;
            for (int i = 0; i < getPointCount(); i++)
                vbo[i].setNormal(normal);
            vao.setBuffers(vbo, ibo);
        }
        const sf::IntRect& getTextureRect() const
        {
            return texRect;
        }

        const sf::Vector2f& getSize() const
        {
            return size;
        }

        virtual unsigned int getPointCount() const
        {
            return 4;
        }

        virtual sf::Vector3f getPoint(std::size_t index) const
        {
            /*switch (index)
            {
            default:
            case 0: return sf::Vector3f(0, 0, 0);
            case 1: return sf::Vector3f(size.x, 0, 0);
            case 2: return sf::Vector3f(size.x, 0, size.y);
            case 3: return sf::Vector3f(0, 0, size.y);
            }*/
            switch (index)
            {
            default:
            case 0: return sf::Vector3f(0, 0, 0);
            case 1: return sf::Vector3f(size.x, 0, 0);
            case 2: return sf::Vector3f(size.x, size.y, 0);
            case 3: return sf::Vector3f(0, size.y, 0);
            }
        }
    private:
        virtual void draw(RenderTarget3D& target, RenderStates3D states) const
        {
            states.transform *= getTransform();
            states.texture = texture;
            target.draw3D(&vao, Triangles, states);
        }
        virtual void update()
        {
            //int count = getPointCount();
            //if (count < 3)
            //{
            //    vbo.resize(0);
            //    return;
            //}

            //for (int i = 0; i < getPointCount(); i++)
            //    vbo[i].setPosition(getPoint(i));
            //updateFillColors();

        }
        void updateTexture()
        {
            sf::FloatRect rect = sf::FloatRect(0.f, 0.f, 1.f, 1.f);
            if (texture)
            {
                if (texRect != sf::IntRect(0, 0, 0, 0))
                {
                    rect = sf::FloatRect((float)texRect.left / texture->getSize().x, (float)texRect.top / texture->getSize().y,
                        (float)texRect.width / texture->getSize().x, (float)texRect.height / texture->getSize().y);
                }
            }
            vbo[0].setTexCoord(rect.left, rect.top);
            vbo[1].setTexCoord(rect.left + rect.width, rect.top);
            vbo[2].setTexCoord(rect.left + rect.width, rect.top + rect.height);
            vbo[3].setTexCoord(rect.left, rect.top + rect.height);
            vao.setBuffers(vbo, ibo);
            /*Vector3f pos[3];
            for (int i = 0; i < 3; i++)
            {
                pos[i] = vbo[i].getPosition();
                pos[i] = getTransform().transformPoint(pos[i]);
            }
            sf::Vector3f normal = CalculateNormal(
                sf::Vector3f(pos[0].x / size.x, pos[0].y, pos[0].z / size.y),
                sf::Vector3f(pos[1].x / size.x, pos[1].y, pos[1].z / size.y),
                sf::Vector3f(pos[2].x / size.x, pos[2].y, pos[2].z / size.y)
            );
            for (int i = 0; i < getPointCount(); i++)
                vbo[i].setNormal(-normal);
           cout << normal.x << endl;
           cout << normal.y << endl;
           cout << normal.z << endl;*/
        }
        const Texture3D* texture = nullptr;
        sf::Vector3f normal;
        sf::IntRect texRect; //20, 20, 20, 20,    (60x60)
        sf::Vector2f size;
    };
}