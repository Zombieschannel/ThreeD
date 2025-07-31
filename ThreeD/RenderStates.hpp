#pragma once
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/CoordinateType.hpp>
#include "Transform.hpp"

namespace DDD
{
    class Texture3D;
    class Shader3D;

	class RenderStates3D
	{
    public:
        RenderStates3D() = default;
        RenderStates3D(const sf::BlendMode& theBlendMode);
        RenderStates3D(const Transform3D& theTransform);
        RenderStates3D(const Texture3D* theTexture);
        RenderStates3D(const Shader3D* theShader);
        RenderStates3D(sf::CoordinateType theCoordinateType);
        RenderStates3D(const sf::BlendMode& theBlendMode, const Transform3D& theTransform, const Texture3D* theTexture, const Shader3D* theShader, sf::CoordinateType theCoordinateType);

        static const RenderStates3D Default;
        sf::BlendMode blendMode{sf::BlendAlpha};
        Transform3D transform;
        const Texture3D* texture = nullptr;
        const Shader3D* shader = nullptr;
		sf::CoordinateType coordinateType{sf::CoordinateType::Pixels};
	};
}