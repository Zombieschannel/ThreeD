#include "RenderStates.hpp"

namespace DDD
{
    const RenderStates3D RenderStates3D::Default(sf::BlendMode(
        sf::BlendMode::Factor::SrcAlpha, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add,
        sf::BlendMode::Factor::One, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add));

    RenderStates3D::RenderStates3D()
        : blendMode(sf::BlendAlpha), transform(), texture(NULL), shader(NULL)
    {

    }
    RenderStates3D::RenderStates3D(const sf::BlendMode &theBlendMode)
        : blendMode(theBlendMode), transform(), texture(NULL), shader(NULL)
    {

    }
    RenderStates3D::RenderStates3D(const Transform3D& theTransform)
        : blendMode(sf::BlendAlpha), transform(theTransform), texture(NULL), shader(NULL)
    {

    }
    RenderStates3D::RenderStates3D(const Texture3D* theTexture)
        : blendMode(sf::BlendAlpha), transform(), texture(theTexture), shader(NULL)
    {

    }
    RenderStates3D::RenderStates3D(const Shader3D* theShader)
        : blendMode(sf::BlendAlpha), transform(), texture(NULL), shader(theShader)
    {

    }
    RenderStates3D::RenderStates3D(const sf::BlendMode &theBlendMode, const Transform3D &theTransform, const Texture3D *theTexture, const Shader3D *theShader)
        : blendMode(theBlendMode), transform(theTransform), texture(theTexture), shader(theShader)
    {

    }
}