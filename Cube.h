#pragma once
#include "Shape.h"
#include "Drawable.h"
#include "RenderTarget.h"
namespace DDD
{
	class Cube3D : public Shape3D, public Drawable3D
	{
	public:
        Cube3D()
        {
            fillColor.resize(getPointCount(), sf::Color(255, 255, 255));
            coord.resize(6);
            update();
        }
        ~Cube3D()
        {

        }
        void setSize(float x, float y, float z)
        {
            this->size = sf::Vector3f(x, y, z);
            update();
        }
        void setSize(const sf::Vector3f& size)
        {
            this->size = size;
            update();
        }
        const sf::Vector3f& getSize() const
        {
            return size;
        }


        virtual unsigned int getPointCount() const
        {
            return 8;
        }

        virtual sf::Vector3f getPoint(std::size_t index) const
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
	private:
        virtual void draw(RenderTarget3D& target, RenderStates3D states) const
        {
            states.transform *= getTransform();
            states.texture = texture;
            target.draw3D(&vao, Triangles, states);
        }
        virtual void update()
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
        const Texture3D* texture = nullptr;
        std::vector<sf::FloatRect> coord;
		sf::Vector3f size;
	};
}