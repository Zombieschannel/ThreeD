#pragma once
#include "Transform.h"
#include "Error.h"
namespace DDD
{
	class View3D
	{
		sf::Vector3f position;
		sf::Vector3f rotation;
		sf::Vector3f origin;
		Transform3D transform;
		sf::IntRect viewPort;
		void setup()
		{
			transform = Transform3D();
			transform.translate(origin);
			transform.rotate(-rotation);
			transform.translate(-position);
		}
	public:
		View3D()
			: position(sf::Vector3f(0, 0, 0)), rotation(sf::Vector3f(0, 0, 0))
		{

		}
		View3D(const sf::IntRect& viewPort)
			: position(sf::Vector3f(0, 0, 0)), rotation(sf::Vector3f(0, 0, 0))
		{
			
			setViewPort(viewPort);
			setup();
		}
		void create(const sf::IntRect& viewPort, const sf::Vector3f& position, const sf::Vector3f& rotation, const sf::Vector3f& origin)
		{
			this->position = position;
			this->rotation = rotation;
			this->origin = origin;
			setViewPort(viewPort);
			setup();
		}
		void setPosition(const sf::Vector3f& position)
		{
			this->position = position;
			setup();
		}
		void move(const sf::Vector3f& move)
		{
			this->position += move;
			setup();
		}

		void setOrigin(const sf::Vector3f& origin)
		{
			this->origin = origin;
			setup();
		}

		void setRotation(const sf::Vector3f& orientation)
		{
			this->rotation = orientation;
			setup();
		}
		void rotate(const sf::Vector3f& rotation)
		{
			this->rotation += rotation;
			setup();
		}

		void setPosition(float x, float y, float z)
		{
			position = sf::Vector3f(x, y, z);
			setup();
		}
		void move(float x, float y, float z)
		{
			position += sf::Vector3f(x, y, z);
			setup();
		}

		void setOrigin(float x, float y, float z)
		{
			origin = sf::Vector3f(x, y, z);
			setup();
		}

		void setRotation(float x, float y, float z)
		{
			rotation = sf::Vector3f(x, y, z);
			setup();
		}
		void rotate(float x, float y, float z)
		{
			rotation += sf::Vector3f(x, y, z);
			setup();
		}
		void setViewPort(const sf::IntRect& rect)
		{
			viewPort = rect;
			GLCall(glViewport(rect.left, rect.top, rect.width, rect.height));
		}

		const sf::Vector3f& getPosition() const
		{
			return position;
		}
		const sf::Vector3f& getRotation() const
		{
			return rotation;
		}
		const sf::Vector3f& getOrigin() const
		{
			return origin;
		}
		const Transform3D& getTransform() const
		{
			return transform;
		}
		const sf::IntRect& getViewPort() const
		{
			return viewPort;
		}
		void NormalizeRotation()
		{
			rotation.x = fmod(rotation.x, 360.0);
			rotation.y = fmod(rotation.y, 360.0);
			rotation.z = fmod(rotation.z, 360.0);

		}
	};
}