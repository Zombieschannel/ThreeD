#pragma once
#include "Transform.h"
namespace DDD
{
	class Transformable3D
	{
        sf::Vector3f origin;
        sf::Vector3f position;
        sf::Vector3f rotation;
        sf::Vector3f Scale;
        mutable Transform3D transform;
        mutable bool needUpdate;
	public:
        Transformable3D()
            : origin(0, 0, 0), position(0, 0, 0), rotation(0, 0, 0), Scale(1, 1, 1), needUpdate(1)
        {

        }
		virtual ~Transformable3D()
		{

		}
        void setPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            needUpdate = 1;
        }
        void setPosition(const sf::Vector3f& position)
        {
            setPosition(position.x, position.y, position.z);
        }
        void setRotation(float angleX, float angleY, float angleZ)
        {
            rotation.x = fmod(angleX, 360);
            rotation.y = fmod(angleY, 360);
            rotation.z = fmod(angleZ, 360);
            needUpdate = 1;
        }
        void setRotation(const sf::Vector3f& angle)
        {
            setRotation(angle.x, angle.y, angle.z);
        }
        void setScale(float scaleX, float scaleY, float scaleZ)
        {
            Scale.x = scaleX;
            Scale.y = scaleY;
            Scale.z = scaleZ;
            needUpdate = 1;
        }
        void setScale(const sf::Vector3f& scale)
        {
            setScale(scale.x, scale.y, scale.z);
        }
        void setOrigin(float x, float y, float z)
        {
            origin.x = x;
            origin.y = y;
            origin.z = z;
            needUpdate = 1;
        }
        void setOrigin(const sf::Vector3f& origin)
        {
            setOrigin(origin.x, origin.y, origin.z);
        }
        const sf::Vector3f& getPosition() const
        {
            return position;
        }
        const sf::Vector3f& getRotation() const
        {
            return rotation;
        }
        const sf::Vector3f& getScale() const
        {
            return Scale;
        }
        const sf::Vector3f& getOrigin() const
        {
            return origin;
        }
        void move(float offsetX, float offsetY, float offsetZ)
        {
            position.x += offsetX;
            position.y += offsetY;
            position.z += offsetZ;
            needUpdate = 1;
        }
        void move(const sf::Vector3f& offset)
        {
            position += offset;
            needUpdate = 1;
        }
        void rotate(float angleX, float angleY, float angleZ)
        {
            rotation.x += angleX;
            rotation.y += angleY;
            rotation.z += angleZ;
            needUpdate = 1;
        }
        void rotate(const sf::Vector3f& angle)
        {
            rotation += angle;
            needUpdate = 1;
        }
        void scale(float scaleX, float scaleY, float scaleZ)
        {
            Scale.x *= scaleX;
            Scale.y *= scaleY;
            Scale.z *= scaleZ;
            needUpdate = 1;
        }
        void scale(const sf::Vector3f& scale_)
        {
            Scale.x *= scale_.x;
            Scale.y *= scale_.y;
            Scale.z *= scale_.z;
            needUpdate = 1;
        }
        const Transform3D& getTransform() const
        {
            if (needUpdate)
            {
                transform = Identity;
                transform.translate(position);
                transform.rotate(rotation);
                transform.scale(Scale);
                transform.translate(-origin);

                needUpdate = 0;
            }
            return transform;
        }
    };
}