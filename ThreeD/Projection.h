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
		float m_near;
		float m_far;
		void setup()
		{
			transform = Transform3D::Perspective(FOV, ratio, m_near, m_far);
		}
	public:
		Projection3D()
			: m_near(0.1f), m_far(1000.f)
		{
			
		}
		Projection3D(float FOV, float ratio, float m_near, float m_far)
		{
			this->ratio = ratio;
			this->m_near = m_near;
			this->m_far = m_far;
			this->FOV = FOV;
			setup();
		}
		Projection3D(const Transform3D& t)
			: m_near(0.1f), m_far(1000.f)
		{
			transform = t;
		}
		void create(float FOV, float ratio, float m_near = 0.1f, float m_far = 1000.f)
		{
			this->ratio = ratio;
			this->m_near = m_near;
			this->m_far = m_far;
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
			this->m_near = m_near;
			setup();
		}
		void setFar(float far)
		{
			this->m_far = m_far;
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
			return m_near;
		}
		const float& getFar() const
		{
			return m_far;
		}
	};
}