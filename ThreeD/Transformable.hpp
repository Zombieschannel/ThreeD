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
		virtual ~Transformable3D() = default;

        void setPosition(sf::Vector3f position);
        void setRotation(sf::Vector3f angle);
        void setScale(sf::Vector3f scale);
        void setOrigin(sf::Vector3f origin);

        const sf::Vector3f& getPosition() const;
        const sf::Vector3f& getRotation() const;
        const sf::Vector3f& getScale() const;
        const sf::Vector3f& getOrigin() const;
        void move(sf::Vector3f offset);
        void rotate(sf::Vector3f angle);
        void scale(sf::Vector3f scale);
        const Transform3D& getTransform() const;
    };
}