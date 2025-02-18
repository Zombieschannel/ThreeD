#include "Transformable.hpp"

namespace DDD
{
    Transformable3D::Transformable3D()
        : _origin(0, 0, 0), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), needUpdate(1)
    {

    }
    Transformable3D::~Transformable3D()
    {

    }
    void Transformable3D::setPosition(const sf::Vector3f& position)
    {
        this->_position.x = position.x;
        this->_position.y = position.y;
        this->_position.z = position.z;
        needUpdate = 1;
    }
    void Transformable3D::setRotation(const sf::Vector3f& angle)
    {
        _rotation.x = fmod(angle.x, 360);
        _rotation.y = fmod(angle.y, 360);
        _rotation.z = fmod(angle.z, 360);
        needUpdate = 1;
    }
    void Transformable3D::setScale(const sf::Vector3f& scale)
    {
        this->_scale.x = scale.x;
        this->_scale.y = scale.y;
        this->_scale.z = scale.z;
        needUpdate = 1;
    }
    void Transformable3D::setOrigin(const sf::Vector3f& origin)
    {
        this->_origin.x = origin.x;
        this->_origin.y = origin.y;
        this->_origin.z = origin.z;
        needUpdate = 1;
    }
    const sf::Vector3f& Transformable3D::getPosition() const
    {
        return _position;
    }
    const sf::Vector3f& Transformable3D::getRotation() const
    {
        return _rotation;
    }
    const sf::Vector3f& Transformable3D::getScale() const
    {
        return _scale;
    }
    const sf::Vector3f& Transformable3D::getOrigin() const
    {
        return _origin;
    }
    void Transformable3D::move(const sf::Vector3f& offset)
    {
        _position += offset;
        needUpdate = 1;
    }
    void Transformable3D::rotate(const sf::Vector3f& angle)
    {
        _rotation += angle;
        needUpdate = 1;
    }
    void Transformable3D::scale(const sf::Vector3f& scale)
    {
        this->_scale.x *= scale.x;
        this->_scale.y *= scale.y;
        this->_scale.z *= scale.z;
        needUpdate = 1;
    }
    const Transform3D& Transformable3D::getTransform() const
    {
        if (needUpdate)
        {
            transform = Transform3D::Identity;
            transform.translate(_position);
            transform.rotate(_rotation);
            transform.scale(_scale);
            transform.translate(-_origin);

            needUpdate = 0;
        }
        return transform;
    }
}