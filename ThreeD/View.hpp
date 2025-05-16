#pragma once
#include "Transform.hpp"
#include "Error.hpp"

namespace DDD
{
	class View3D
	{
		sf::Vector3f position;
		sf::Vector3f rotation;
		sf::Vector3f origin;
		Transform3D transform;
		void setup();
	public:
		View3D();
			
		void create(sf::Vector3f position, sf::Vector3f rotation, sf::Vector3f origin);
		void setPosition(sf::Vector3f position);
		void move(sf::Vector3f move);
		void setOrigin(sf::Vector3f origin);
		void setRotation(sf::Vector3f orientation);
		void rotate(sf::Vector3f rotation);

		sf::Vector3f getPosition() const;
		sf::Vector3f getRotation() const;
		sf::Vector3f getOrigin() const;
		const Transform3D& getTransform() const;
	};
}