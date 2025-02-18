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
    Projection3D::Projection3D(float FOV, float ratio, float _near, float _far)
    {
        this->ratio = ratio;
        this->_near = _near;
        this->_far = _far;
        this->FOV = FOV;
        setup();
    }
    Projection3D::Projection3D(const Transform3D& t)
    : _near(0.1f), _far(1000.f)
    {
        transform = t;
    }
    void Projection3D::create(float FOV, float ratio, float _near, float _far)
    {
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
}