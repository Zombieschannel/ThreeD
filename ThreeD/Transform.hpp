#pragma once
#include <cmath>
#include <array>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include "Error.hpp"

namespace DDD
{
	class Transform3D
	{
    public:
        Transform3D();

        Transform3D(float a00, float a01, float a02, float a03,
                    float a10, float a11, float a12, float a13,
                    float a20, float a21, float a22, float a23,
                    float a30, float a31, float a32, float a33);

        const float* getMatrix() const;
        sf::Vector3f transformPoint(sf::Vector3f point) const;
        Transform3D transpose() const;

        static Transform3D Perspective(sf::Angle fov, float aspect, float near, float m_far);
        static Transform3D Ortho(float left, float right, float top, float bottom, float m_near, float m_far);

        Transform3D& combine(const Transform3D& transform);
        Transform3D& translate(sf::Vector3f offset);
        Transform3D& rotate(sf::Vector3f angle);
        Transform3D& scale(sf::Vector3f factors);
        Transform3D& scale(sf::Vector3f factors, sf::Vector3f center);

        static const Transform3D Identity;
    private:
        std::array<float, 16> matrix{1.f, 0.f, 0.f, 0.f,
                                     0.f, 1.f, 0.f, 0.f,
                                     0.f, 0.f, 1.f, 0.f,
                                     0.f, 0.f, 0.f, 1.f};
    };
    
    Transform3D operator*(const Transform3D& left, const Transform3D& right);
    Transform3D& operator*=(Transform3D& left, const Transform3D& right);
    sf::Vector3f operator*(const Transform3D& left, const sf::Vector3f& right);
    bool operator ==(const Transform3D& left, const Transform3D& right);
    bool operator !=(const Transform3D& left, const Transform3D& right);
}