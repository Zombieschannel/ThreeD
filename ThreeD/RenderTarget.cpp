#include "RenderTarget.hpp"

namespace DDD
{
    RenderTarget3D::~RenderTarget3D()
    {

    }
    void RenderTarget3D::clear3D(const ColorF color, std::uint32_t clearCall)
    {
        GLCall(glClearColor(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0));
        GLCall(glClear(clearCall));
    }
    void RenderTarget3D::setView3D(const View3D& view)
    {
        this->view = view;
    }
    const View3D& RenderTarget3D::getView3D() const
    {
        return view;
    }
    void RenderTarget3D::setProjection3D(const Projection3D& proj)
    {
        this->proj = proj;
    }
    const Projection3D& RenderTarget3D::getProjection3D() const
    {
        return proj;
    }
    void RenderTarget3D::draw3D(const Drawable3D& drawable, const RenderStates3D& states)
    {
        drawable.draw(*this, states);
    }
    RenderTarget3D::RenderTarget3D()
    {

    }
}