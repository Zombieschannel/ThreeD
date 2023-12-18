#pragma once
#include "BlendMode.h"
#include "Transform.h"
#include "Material.h"
namespace DDD
{
    class Texture3D;
    class Shader3D;

	class RenderStates3D
	{
    public:
        RenderStates3D()
            : blendMode(BlendAlpha), transform(), texture(NULL), shader(NULL), material(NULL)
        {

        }
        RenderStates3D(const BlendMode3D& theBlendMode3D)
            : blendMode(theBlendMode3D), transform(), texture(NULL), shader(NULL), material(NULL)
        {

        }
        RenderStates3D(const Transform3D& theTransform)
            : blendMode(BlendAlpha), transform(theTransform), texture(NULL), shader(NULL), material(NULL)
        {

        }
        RenderStates3D(const Texture3D* theTexture)
            : blendMode(BlendAlpha), transform(), texture(theTexture), shader(NULL), material(NULL)
        {

        }
        RenderStates3D(const Shader3D* theShader)
            : blendMode(BlendAlpha), transform(), texture(NULL), shader(theShader), material(NULL)
        {

        }
        RenderStates3D(const Material3D* theMaterial)
            : blendMode(BlendAlpha), transform(), texture(NULL), shader(NULL), material(theMaterial)
        {

        }
        RenderStates3D(const BlendMode3D& theBlendMode3D, const Transform3D& theTransform,
            const Texture3D* theTexture, const Shader3D* theShader, const Material3D* theMaterial)
            : blendMode(theBlendMode3D), transform(theTransform), texture(theTexture), shader(theShader), material(theMaterial)
        {

        }
        static const RenderStates3D Default;
        BlendMode3D blendMode;
        Transform3D transform;
        const Texture3D* texture;
        const Shader3D* shader;
        const Material3D* material;
	};
    inline const RenderStates3D RenderStates3D::Default(BlendMode3D(
        BlendMode3D::SrcAlpha, BlendMode3D::OneMinusSrcAlpha, BlendMode3D::Add,
        BlendMode3D::One, BlendMode3D::OneMinusSrcAlpha, BlendMode3D::Add));
}