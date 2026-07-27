#include "Projection.hpp"

namespace DDD
{
    void Projection3D::setup()
    {
        transform = Transform3D::Perspective(FOV, ratio, near, far);
    }
    Projection3D::Projection3D()
        : near(0.1f), far(1000.f)
    {
        
    }
    Projection3D::Projection3D(const sf::IntRect& viewPort)
    : near(0.1f), far(1000.f)
    {
        setViewport(viewPort);
    }
    Projection3D::Projection3D(const sf::Angle FOV, const float ratio, const float near, const float far)
    {
        this->ratio = ratio;
        this->near = near;
        this->far = far;
        this->FOV = FOV;
        setup();
    }
    Projection3D::Projection3D(const Transform3D& transform)
        : near(0.1f), far(1000.f)
    {
        this->transform = transform;
    }
    void Projection3D::create(const sf::IntRect& viewPort, const sf::Angle FOV, const float ratio, const float near, const float far)
    {
        this->viewPort = viewPort;
        this->ratio = ratio;
        this->near = near;
        this->far = far;
        this->FOV = FOV;
        setup();
    }
    void Projection3D::setFov(const sf::Angle angle)
    {
        FOV = angle;
        setup();
    }
    void Projection3D::setNear(const float near)
    {
        this->near = near;
        setup();
    }
    void Projection3D::setFar(const float far)
    {
        this->far = far;
        setup();
    }
    void Projection3D::setAspectRatio(const float ratio)
    {
        this->ratio = ratio;
        setup();
    }
    void Projection3D::setViewport(const sf::IntRect& rect)
    {
        viewPort = rect;
    }
    void Projection3D::setTransform(const Transform3D& transform)
    {
        this->transform = transform;
    }
    sf::Angle Projection3D::getFov() const
    {
        return FOV;
    }
    const Transform3D& Projection3D::getTransform() const
    {
        return transform;
    }
    float Projection3D::getNear() const
    {
        return near;
    }
    float Projection3D::getFar() const
    {
        return far;
    }
    const sf::IntRect& Projection3D::getViewport() const
    {
        return viewPort;
    }
}