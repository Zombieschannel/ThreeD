#pragma once
#include "Transform.hpp"
#include "Error.hpp"

namespace DDD
{
	class Projection3D
	{
		Transform3D transform;
		float FOV = 90;
		float ratio = 0;
		float _near;
		float _far;
		void setup();
	public:
		Projection3D();
		Projection3D(float FOV, float ratio, float _near, float _far);
		Projection3D(const Transform3D& t);
		void create(float FOV, float ratio, float _near = 0.1f, float _far = 1000.f);
		void setFov(float degrees);
		void setNear(float _near);
		void setFar(float _far);

		void setAspectRatio(float ratio);
		const float getFov() const;
		const Transform3D& getTransform() const;
		const float getNear() const;
		const float getFar() const;
	};
}