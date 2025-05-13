#include "RenderStates.hpp"

#include <SFML/Graphics/CoordinateType.hpp>

namespace DDD
{
    const RenderStates3D RenderStates3D::Default(sf::BlendMode(
        sf::BlendMode::Factor::SrcAlpha, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add,
        sf::BlendMode::Factor::One, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add));

    RenderStates3D::RenderStates3D(const sf::BlendMode &theBlendMode)
        : blendMode(theBlendMode)
    {

    }
    RenderStates3D::RenderStates3D(const Transform3D& theTransform)
        : transform(theTransform)
    {

    }
    RenderStates3D::RenderStates3D(const Texture3D* theTexture)
        : texture(theTexture)
    {

    }
    RenderStates3D::RenderStates3D(const Shader3D* theShader)
        : shader(theShader)
    {

    }
    RenderStates3D::RenderStates3D(const sf::CoordinateType theCoordinateType)
    : coordinateType(theCoordinateType)
    {

    }
    RenderStates3D::RenderStates3D(const sf::BlendMode &theBlendMode, const Transform3D &theTransform, const Texture3D *theTexture, const Shader3D *theShader, const sf::CoordinateType theCoordinateType)
        : blendMode(theBlendMode), transform(theTransform), texture(theTexture), shader(theShader), coordinateType(theCoordinateType)
    {

    }
}
