#pragma once
#include <SFML/Graphics/Color.hpp>
#include "Shader.h"
namespace DDD
{
	class PointLight3D : public Light3D
	{
		DDD::ColorF lightColor;
		float quadratic;
		float linear;
		sf::Vector3f pos;
	public:
		PointLight3D()
			: lightColor(1.f),
			quadratic(0.01), linear(0.01), pos(0, 0, 0)
		{

		}
		~PointLight3D()
		{

		}
		void setColor(const DDD::ColorF& color)
		{
			lightColor = color;
		}
		void setQuadraticFallof(float Quadratic)
		{
			quadratic = Quadratic;
		}
		void setLinearFallof(float Linear)
		{
			linear = Linear;
		}
		void setPosition(float x, float y, float z)
		{
			pos.x = x;
			pos.y = y;
			pos.z = z;
		}
		void setPosition(const sf::Vector3f& position)
		{
			setPosition(position.x, position.y, position.z);
		}

		const DDD::ColorF& getColor() const
		{
			return lightColor;
		}
		float getQuadraticFallof() const
		{
			return quadratic;
		}
		float getLinearFallof() const
		{
			return linear;
		}
		sf::Vector3f getPosition() const
		{
			return pos;
		}
	private:
		virtual void setUniforms(const Shader3D* shader, const int index) const
		{
			shader->setUniform("pointLights[" + std::to_string(index) + "].pos", pos);
			shader->setUniform("pointLights[" + std::to_string(index) + "].col", lightColor);
			shader->setUniform("pointLights[" + std::to_string(index) + "].quadratic", quadratic);
			shader->setUniform("pointLights[" + std::to_string(index) + "].linear", linear);
		}
	};

	class DirectionalLight3D : public Light3D
	{
		DDD::ColorF lightColor;
		sf::Vector3f dir;
	public:
		DirectionalLight3D()
			: lightColor(1.f), dir(0, 0, 0)
		{

		}
		~DirectionalLight3D()
		{

		}
		void setColor(const DDD::ColorF& color)
		{
			lightColor = color;
		}
		void setDirection(float factorX, float factorY, float factorZ)
		{
			dir.x = factorX;
			dir.y = factorY;
			dir.z = factorZ;
		}
		void setDirection(const sf::Vector3f& factors)
		{
			setDirection(factors.x, factors.y, factors.z);
		}

		const DDD::ColorF& getColor() const
		{
			return lightColor;
		}
		sf::Vector3f getDirection() const
		{
			return dir;
		}
	private:
		virtual void setUniforms(const Shader3D* shader, const int index) const
		{
			shader->setUniform("directionalLights[" + std::to_string(index) + "].dir", dir);
			shader->setUniform("directionalLights[" + std::to_string(index) + "].col", lightColor);
		}
	};

	class SpotLight3D : public Light3D
	{
		DDD::ColorF lightColor;
		float quadratic;
		float linear;
		float outerCone;
		float innerCone;
		sf::Vector3f dir;
		sf::Vector3f pos;
	public:
		SpotLight3D()
			: lightColor(1.f),
			quadratic(0.01), linear(0.01), outerCone(25), innerCone(18),
			dir(0, 0, 0), pos(0, 0, 0)
		{

		}
		~SpotLight3D()
		{

		}
		void setColor(const DDD::ColorF& color)
		{
			lightColor = color;
		}
		void setQuadraticFallof(float Quadratic)
		{
			quadratic = Quadratic;
		}
		void setLinearFallof(float Linear)
		{
			linear = Linear;
		}
		void setOuterCone(float OuterCone)
		{
			outerCone = OuterCone;
		}
		void setInnerCone(float InnerCone)
		{
			innerCone = InnerCone;
		}
		void setPosition(float x, float y, float z)
		{
			pos.x = x;
			pos.y = y;
			pos.z = z;
		}
		void setPosition(const sf::Vector3f& position)
		{
			setPosition(position.x, position.y, position.z);
		}
		void setDirection(float factorX, float factorY, float factorZ)
		{
			dir.x = factorX;
			dir.y = factorY;
			dir.z = factorZ;
		}
		void setDirection(const sf::Vector3f& factors)
		{
			setDirection(factors.x, factors.y, factors.z);
		}

		const DDD::ColorF& getColor() const
		{
			return lightColor;
		}
		float getQuadraticFallof() const
		{
			return quadratic;
		}
		float getLinearFallof() const
		{
			return linear;
		}
		float getOuterCone() const
		{
			return outerCone;
		}
		float getInnerCone() const
		{
			return innerCone;
		}
		sf::Vector3f getPosition() const
		{
			return pos;
		}
		sf::Vector3f getDirection() const
		{
			return dir;
		}
	private:
		virtual void setUniforms(const Shader3D* shader, const int index) const
		{
			shader->setUniform("spotLights[" + std::to_string(index) + "].pos", pos);
			shader->setUniform("spotLights[" + std::to_string(index) + "].dir", dir);
			shader->setUniform("spotLights[" + std::to_string(index) + "].col", lightColor);
			shader->setUniform("spotLights[" + std::to_string(index) + "].quadratic", quadratic);
			shader->setUniform("spotLights[" + std::to_string(index) + "].linear", linear);
			shader->setUniform("spotLights[" + std::to_string(index) + "].outer", std::cos(outerCone * 0.0174533f));
			shader->setUniform("spotLights[" + std::to_string(index) + "].inner", std::cos(innerCone * 0.0174533f));
		}
	};
}