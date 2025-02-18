#pragma once
#include "RenderStates.hpp"

namespace DDD
{
    class RenderTarget3D;

    class Drawable3D
    {
    public:
        virtual ~Drawable3D() {}
    protected:
        friend class RenderTarget3D;

        virtual void draw(RenderTarget3D& target, RenderStates3D states) const = 0;
    };
}