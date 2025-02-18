#pragma once
#include "Transform.hpp"

namespace DDD
{
	class Transformable3D
	{
        sf::Vector3f _origin;
        sf::Vector3f _position;
        sf::Vector3f _rotation;
        sf::Vector3f _scale;
        mutable Transform3D transform;
        mutable bool needUpdate;
	public:
        Transformable3D();
		virtual ~Transformable3D();

        void setPosition(const sf::Vector3f& position);
        void setRotation(const sf::Vector3f& angle);
        void setScale(const sf::Vector3f& scale);
        void setOrigin(const sf::Vector3f& origin);

        const sf::Vector3f& getPosition() const;
        const sf::Vector3f& getRotation() const;
        const sf::Vector3f& getScale() const;
        const sf::Vector3f& getOrigin() const;
        void move(const sf::Vector3f& offset);
        void rotate(const sf::Vector3f& angle);
        void scale(const sf::Vector3f& scale);
        const Transform3D& getTransform() const;
    };
}