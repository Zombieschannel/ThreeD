#pragma once
#include "Transform.h"
#include "Error.h"
namespace DDD
{
	class Projection3D
	{
		Transform3D transform;
		float FOV = 90;
		float ratio = 0;
		float near;
		float far;
		void setup()
		{
			transform = Transform3D::Perspective(FOV, ratio, near, far);
		}
	public:
		Projection3D()
			: near(0.1f), far(1000.f)
		{
			
		}
		Projection3D(float FOV, float ratio, float near, float far)
		{
			this->ratio = ratio;
			this->near = near;
			this->far = far;
			this->FOV = FOV;
			setup();
		}
		Projection3D(const Transform3D& t)
			: near(0.1f), far(1000.f)
		{
			transform = t;
		}
		void create(float FOV, float ratio, float near = 0.1f, float far = 1000.f)
		{
			this->ratio = ratio;
			this->near = near;
			this->far = far;
			this->FOV = FOV;
			setup();
		}
		void setFov(float degrees)
		{
			FOV = degrees;
			setup();
		}
		void setNear(float near)
		{
			this->near = near;
			setup();
		}
		void setFar(float far)
		{
			this->far = far;
			setup();
		}

		void setAspectRatio(float ratio)
		{
			this->ratio = ratio;
			setup();
		}
		const float& getFov() const
		{
			return FOV;
		}
		const Transform3D& getTransform() const
		{
			return transform;
		}
		const float& getNear() const
		{
			return near;
		}
		const float& getFar() const
		{
			return far;
		}
	};
}