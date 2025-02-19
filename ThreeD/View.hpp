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
			
		void create(const sf::Vector3f position, const sf::Vector3f rotation, const sf::Vector3f origin);
		void setPosition(const sf::Vector3f position);
		void move(const sf::Vector3f move);
		void setOrigin(const sf::Vector3f origin);
		void setRotation(const sf::Vector3f orientation);
		void rotate(const sf::Vector3f rotation);

		sf::Vector3f getPosition() const;
		sf::Vector3f getRotation() const;
		sf::Vector3f getOrigin() const;
		const Transform3D& getTransform() const;

		void NormalizeRotation();
	};
}