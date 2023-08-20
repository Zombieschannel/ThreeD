#pragma once
#include "OGL.h"
namespace DDD
{
    struct BlendMode3D
    {
        enum Factor
        {
            Zero = GL_ZERO,
            One = GL_ONE,
            SrcColor = GL_SRC_COLOR,
            OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
            DstColor = GL_DST_COLOR,
            OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
            SrcAlpha = GL_SRC_ALPHA,
            OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
            DstAlpha = GL_DST_ALPHA,
            OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
        };
        enum Equation
        {
            Add = GL_FUNC_ADD,
            Subtract = GL_FUNC_SUBTRACT,
            ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
#if not defined(GLES20)
            Min = GL_MIN,
            Max = GL_MAX,
#endif
        };
        BlendMode3D()
            : colorSrcFactor(BlendMode3D::SrcAlpha),
            colorDstFactor(BlendMode3D::OneMinusSrcAlpha),
            colorEquation(BlendMode3D::Add),
            alphaSrcFactor(BlendMode3D::One),
            alphaDstFactor(BlendMode3D::OneMinusSrcAlpha),
            alphaEquation(BlendMode3D::Add)
        {

        }

        BlendMode3D(Factor sourceFactor, Factor destinationFactor, Equation blendEquation = Add)
            : colorSrcFactor(sourceFactor),
            colorDstFactor(destinationFactor),
            colorEquation(blendEquation),
            alphaSrcFactor(sourceFactor),
            alphaDstFactor(destinationFactor),
            alphaEquation(blendEquation)
        {

        }

        BlendMode3D(Factor colorSourceFactor, Factor colorDestinationFactor,
            Equation colorBlendEquation, Factor alphaSourceFactor,
            Factor alphaDestinationFactor, Equation alphaBlendEquation)
            : colorSrcFactor(colorSourceFactor),
            colorDstFactor(colorDestinationFactor),
            colorEquation(colorBlendEquation),
            alphaSrcFactor(alphaSourceFactor),
            alphaDstFactor(alphaDestinationFactor),
            alphaEquation(alphaBlendEquation)
        {

        }

        Factor colorSrcFactor;
        Factor colorDstFactor;
        Equation colorEquation;
        Factor alphaSrcFactor;
        Factor alphaDstFactor;
        Equation alphaEquation;
    };
    bool operator ==(const BlendMode3D& left, const BlendMode3D& right)
    {
        return (left.colorSrcFactor == right.colorSrcFactor) &&
            (left.colorDstFactor == right.colorDstFactor) &&
            (left.colorEquation == right.colorEquation) &&
            (left.alphaSrcFactor == right.alphaSrcFactor) &&
            (left.alphaDstFactor == right.alphaDstFactor) &&
            (left.alphaEquation == right.alphaEquation);
    }
    bool operator !=(const BlendMode3D& left, const BlendMode3D& right)
    {
        return !(left == right);
    }
    const BlendMode3D BlendAlpha(BlendMode3D::SrcAlpha, BlendMode3D::OneMinusSrcAlpha, BlendMode3D::Add,
        BlendMode3D::One, BlendMode3D::OneMinusSrcAlpha, BlendMode3D::Add);
    const BlendMode3D BlendAdd(BlendMode3D::SrcAlpha, BlendMode3D::One, BlendMode3D::Add,
        BlendMode3D::One, BlendMode3D::One, BlendMode3D::Add);
    const BlendMode3D BlendMultiply(BlendMode3D::DstColor, BlendMode3D::Zero, BlendMode3D::Add);
#if not defined(GLES20)
    const BlendMode3D BlendMin(BlendMode3D::One, BlendMode3D::One, BlendMode3D::Min);
    const BlendMode3D BlendMax(BlendMode3D::One, BlendMode3D::One, BlendMode3D::Max);
#endif
    const BlendMode3D BlendNone(BlendMode3D::One, BlendMode3D::Zero, BlendMode3D::Add);

} 