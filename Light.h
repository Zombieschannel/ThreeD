#pragma once
namespace DDD
{
	class Shader3D;
	class Light3D
	{
		friend class Shader3D;
	protected:
		virtual void setUniforms(const Shader3D* shader, const int index) const = 0;
	};
}