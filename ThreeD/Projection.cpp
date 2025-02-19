#include "Projection.hpp"

namespace DDD
{
    void DDD::Projection3D::setup()
    {
        transform = Transform3D::Perspective(FOV, ratio, _near, _far);
    }
    Projection3D::Projection3D()
        : _near(0.1f), _far(1000.f)
    {
        
    }
    Projection3D::Projection3D(const sf::IntRect& viewPort)
    : _near(0.1f), _far(1000.f)
    {
        setViewport(viewPort);
    }
    Projection3D::Projection3D(float FOV, float ratio, float _near, float _far)
    {
        this->ratio = ratio;
        this->_near = _near;
        this->_far = _far;
        this->FOV = FOV;
        setup();
    }
    Projection3D::Projection3D(const Transform3D& transform)
        : _near(0.1f), _far(1000.f)
    {
        this->transform = transform;
    }
    void Projection3D::create(const sf::IntRect& viewPort, float FOV, float ratio, float _near, float _far)
    {
        this->viewPort = viewPort;
        this->ratio = ratio;
        this->_near = _near;
        this->_far = _far;
        this->FOV = FOV;
        setup();
    }
    void Projection3D::setFov(float degrees)
    {
        FOV = degrees;
        setup();
    }
    void Projection3D::setNear(float _near)
    {
        this->_near = _near;
        setup();
    }
    void Projection3D::setFar(float _far)
    {
        this->_far = _far;
        setup();
    }
    void Projection3D::setAspectRatio(float ratio)
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
    const float Projection3D::getFov() const
    {
        return FOV;
    }
    const Transform3D& Projection3D::getTransform() const
    {
        return transform;
    }
    const float Projection3D::getNear() const
    {
        return _near;
    }
    const float Projection3D::getFar() const
    {
        return _far;
    }
    const sf::IntRect& Projection3D::getViewport() const
    {
        return viewPort;
    }
}