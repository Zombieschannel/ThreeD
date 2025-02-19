#include "View.hpp"

namespace DDD
{
    void View3D::setup()
    {
        transform = Transform3D();
        transform.translate(origin);
        transform.rotate(-rotation);
        transform.translate(-position);
    }
    View3D::View3D()
        : position(sf::Vector3f(0, 0, 0)), rotation(sf::Vector3f(0, 0, 0)), origin(sf::Vector3f(0, 0, 0))
    {
    }
    void View3D::create(const sf::Vector3f position, const sf::Vector3f rotation, const sf::Vector3f origin)
    {
        this->position = position;
        this->rotation = rotation;
        this->origin = origin;
        setup();
    }
    void View3D::setPosition(const sf::Vector3f position)
    {
        this->position = position;
        setup();
    }
    void View3D::move(const sf::Vector3f move)
    {
        this->position += move;
        setup();
    }
    void View3D::setOrigin(const sf::Vector3f origin)
    {
        this->origin = origin;
        setup();
    }
    void View3D::setRotation(const sf::Vector3f orientation)
    {
        this->rotation = orientation;
        setup();
    }
    void View3D::rotate(const sf::Vector3f rotation)
    {
        this->rotation += rotation;
        setup();
    }
    sf::Vector3f View3D::getPosition() const
    {
        return position;
    }
    sf::Vector3f View3D::getRotation() const
    {
        return rotation;
    }
    sf::Vector3f View3D::getOrigin() const
    {
        return origin;
    }
    const Transform3D& View3D::getTransform() const
    {
        return transform;
    }
    void View3D::NormalizeRotation()
    {
        rotation.x = fmod(rotation.x, 360.0);
        rotation.y = fmod(rotation.y, 360.0);
        rotation.z = fmod(rotation.z, 360.0);
    }
}