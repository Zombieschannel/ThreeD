#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Transform.hpp"
#include "Error.hpp"

namespace DDD
{
	class Projection3D
	{
		Transform3D transform;
		sf::Angle FOV = sf::degrees(90);
		float ratio = 0;
		float near;
		float far;
		sf::IntRect viewPort;
		void setup();
	public:
		Projection3D();
		Projection3D(const sf::IntRect& viewPort);
		Projection3D(sf::Angle FOV, float ratio, float near, float far);
		Projection3D(const Transform3D& transform);

		void create(const sf::IntRect& viewPort, sf::Angle FOV, float ratio, float _near = 0.1f, float _far = 1000.f);
		void setFov(sf::Angle angle);
		void setNear(float _near);
		void setFar(float _far);
		void setAspectRatio(float ratio);
		void setViewport(const sf::IntRect& rect);
		void setTransform(const Transform3D& transform);

		sf::Angle getFov() const;
		const Transform3D& getTransform() const;
		float getNear() const;
		float getFar() const;
		const sf::IntRect& getViewport() const;
	};
}