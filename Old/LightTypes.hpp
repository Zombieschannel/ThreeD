#pragma once
#include <SFML/Graphics/Color.hpp>
#include "Shader.hpp"

namespace DDD
{
	class PointLight3D : public Light3D
	{
		ColorF lightColor;
		float quadratic;
		float linear;
		sf::Vector3f position;
	public:
		PointLight3D()
			: lightColor(1.f),
			quadratic(0.01), linear(0.01), position(0, 0, 0)
		{

		}
		~PointLight3D()
		{

		}
		void setColor(const DDD::ColorF& color)
		{
			this->lightColor = color;
		}
		void setQuadraticFalloff(float quadratic)
		{
			this->quadratic = Quadratic;
		}
		void setLinearFalloff(float linear)
		{
			this->linear = linear;
		}
		void setPosition(const sf::Vector3f& position)
		{
			this->position = position;
		}

		const DDD::ColorF& getColor() const
		{
			return lightColor;
		}
		float getQuadraticFalloff() const
		{
			return quadratic;
		}
		float getLinearFalloff() const
		{
			return linear;
		}
		sf::Vector3f getPosition() const
		{
			return position;
		}
	private:
		virtual void setUniforms(const Shader3D* shader, const int index) const
		{
			shader->setUniform("pointLights[" + std::to_string(index) + "].pos", position);
			shader->setUniform("pointLights[" + std::to_string(index) + "].col", lightColor);
			shader->setUniform("pointLights[" + std::to_string(index) + "].quadratic", quadratic);
			shader->setUniform("pointLights[" + std::to_string(index) + "].linear", linear);
		}
	};

	class DirectionalLight3D : public Light3D
	{
		ColorF lightColor;
		sf::Vector3f direction;
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

		void setDirection(const sf::Vector3f& direction)
		{
			this->direction = direction;
		}

		const DDD::ColorF& getColor() const
		{
			return lightColor;
		}
		sf::Vector3f getDirection() const
		{
			return direction;
		}
	private:
		virtual void setUniforms(const Shader3D* shader, const int index) const
		{
			shader->setUniform("directionalLights[" + std::to_string(index) + "].dir", direction);
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
		sf::Vector3f direction;
		sf::Vector3f position;
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
			this->lightColor = color;
		}
		void setQuadraticFalloff(float quadratic)
		{
			this->quadratic = quadratic;
		}
		void setLinearFalloff(float linear)
		{
			this->linear = linear;
		}
		void setOuterCone(float outerCone)
		{
			this->outerCone = outerCone;
		}
		void setInnerCone(float innerCone)
		{
			this->innerCone = innerCone;
		}
		void setPosition(const sf::Vector3f& position)
		{
			this->position = position;
		}
		void setDirection(const sf::Vector3f& direction)
		{
			this->direction = direction;
		}

		const DDD::ColorF& getColor() const
		{
			return lightColor;
		}
		float getQuadraticFalloff() const
		{
			return quadratic;
		}
		float getLinearFalloff() const
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
			return position;
		}
		sf::Vector3f getDirection() const
		{
			return direction;
		}
	private:
		virtual void setUniforms(const Shader3D* shader, const int index) const
		{
			shader->setUniform("spotLights[" + std::to_string(index) + "].pos", position);
			shader->setUniform("spotLights[" + std::to_string(index) + "].dir", direction);
			shader->setUniform("spotLights[" + std::to_string(index) + "].col", lightColor);
			shader->setUniform("spotLights[" + std::to_string(index) + "].quadratic", quadratic);
			shader->setUniform("spotLights[" + std::to_string(index) + "].linear", linear);
			shader->setUniform("spotLights[" + std::to_string(index) + "].outer", std::cos(outerCone * 0.0174533f));
			shader->setUniform("spotLights[" + std::to_string(index) + "].inner", std::cos(innerCone * 0.0174533f));
		}
	};
}