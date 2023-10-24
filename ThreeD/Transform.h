#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include "Error.h"
namespace DDD
{
	class Transform3D
	{
    public:
        Transform3D()
            : matrix{ 1.f, 0.f, 0.f, 0.f,
                      0.f, 1.f, 0.f, 0.f,
                      0.f, 0.f, 1.f, 0.f,
                      0.f, 0.f, 0.f, 1.f}
        {

        }

            
        Transform3D(float a00, float a01, float a02, float a03,
                    float a10, float a11, float a12, float a13,
                    float a20, float a21, float a22, float a23,
                    float a30, float a31, float a32, float a33)
            : matrix{ a00, a01, a02, a03,
                      a10, a11, a12, a13,
                      a20, a21, a22, a23,
                      a30, a31, a32, a33 }
        {

        }

        const float* getMatrix() const
        {
            return &matrix[0][0];
        }
        /*Transform3D getInverse() const
        {

        }*/

        sf::Vector3f transformPoint(float x, float y, float z) const
        {
            return sf::Vector3f(matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3],
                                matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3],
                                matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3]);
        }

        sf::Vector3f transformPoint(const sf::Vector3f& point) const
        {
            return transformPoint(point.x, point.y, point.z);
        }

       /* sf::FloatRect transformRect(const sf::FloatRect& rectangle) const
        {

        }*/
        Transform3D transpose() const
        {
            return Transform3D(
                    matrix[0][0], matrix[1][0],matrix[2][0],matrix[3][0],
                    matrix[0][1], matrix[1][1],matrix[2][1],matrix[3][1],
                    matrix[0][2], matrix[1][2],matrix[2][2],matrix[3][2],
                    matrix[0][3], matrix[1][3],matrix[2][3],matrix[3][3]
            );
        }
        static Transform3D Perspective(float fov, float aspect, float m_near, float m_far)
        {
            float tanHalfFovy = tan((fov * 0.0174533) / 2);
            float a = 1 / (aspect * tanHalfFovy);
            float b = 1 / tanHalfFovy;
            float c = -(m_far + m_near) / (m_far - m_near);
            float d = -(2 * m_far * m_near) / (m_far - m_near);

            return Transform3D(a, 0, 0, 0,
                               0, b, 0, 0,
                               0, 0, c, d,
                               0, 0, -1, 0);
        }
        static Transform3D Ortho(float left, float right, float top, float bottom, float m_near, float m_far)
        {
            float tx = (right + left) / (right - left);
            float ty = (top + bottom) / (top - bottom);
            float tz = (m_far + m_near) / (m_far - m_near);
            tx = -tx;
            ty = -ty;
            tz = -tz;

            float a = 2 / (right - left);
            float b = 2 / (top - bottom);
            float c = -2 / (m_far - m_near);

            return Transform3D(a, 0, 0, tx,
                               0, b, 0, ty,
                               0, 0, c, tz,
                               0, 0, 0, 1);
        }

        Transform3D& combine(const Transform3D& transform)
        {
            const float* a = &matrix[0][0];
            const float* b = &transform.matrix[0][0];

          
            Transform3D newTransform;
            for (int I = 0; I < 4; ++I)
            {
                for (int J = 0; J < 4; ++J)
                {
                    float SumElements = 0.0f;
                    for (int K = 0; K < 4; ++K)
                    {
                        SumElements += this->matrix[I][K] * transform.matrix[K][J];
                    }
                    newTransform.matrix[I][J] = SumElements;
                }
            }
            *this = newTransform;
            return *this;
        }

        Transform3D& translate(float x, float y, float z)
        {
            return translate(sf::Vector3f(x, y, z));
        }

        Transform3D& translate(const sf::Vector3f& offset)
        {
            Transform3D translation(1, 0, 0, offset.x,
                                    0, 1, 0, offset.y,
                                    0, 0, 1, offset.z,
                                    0, 0, 0, 1);

            return combine(translation);
        }

        Transform3D& rotate(sf::Vector3f angle)
        {
            return rotate(angle.x, angle.y, angle.z);
        }

        Transform3D& rotate(float angleX, float angleY, float angleZ)
        {
            float radX = angleX * 3.141592654f / 180.f;
            float cosX = std::cos(radX);
            float sinX = std::sin(radX);
            Transform3D rotationX(  1,  0,      0, 0,
                                    0, cosX, -sinX, 0,
                                    0, sinX, cosX, 0,
                                    0,  0,      0, 1);

            float radY = angleY * 3.141592654f / 180.f;
            float cosY = std::cos(radY);
            float sinY = std::sin(radY);

            Transform3D rotationY(cosY, 0, sinY, 0,
                                  0, 1, 0, 0,
                                  -sinY, 0, cosY, 0,
                                  0, 0, 0, 1);

            float radZ = angleZ * 3.141592654f / 180.f;
            float cosZ = std::cos(radZ);
            float sinZ = std::sin(radZ);

            Transform3D rotationZ(cosZ, -sinZ, 0, 0,
                                  sinZ, cosZ, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);


            return combine(rotationX).combine(rotationY).combine(rotationZ);
        }

        /*Transform3D& rotate(float angleX, float angleY, float angleZ, float centerX, float centerY, float centerZ)
        {

        }

        Transform3D& rotate(sf::Vector3f angle, const sf::Vector3f& center)
        {
            return rotate(angle.x, angle.y, angle.z, center.x, center.y, center.z);
        }*/

        Transform3D& scale(float scaleX, float scaleY, float scaleZ)
        {
            return scale(sf::Vector3f(scaleX, scaleY, scaleZ));
        }

        Transform3D& scale(float scaleX, float scaleY, float scaleZ, float centerX, float centerY, float centerZ)
        {
            Transform3D scaling(scaleX, 0, 0, centerX * (1 - scaleX),
                                0, scaleY, 0, centerY * (1 - scaleY),
                                0, 0, scaleZ, centerZ * (1 - scaleZ),
                                0, 0, 0, 1);

            return combine(scaling);
        }

        Transform3D& scale(const sf::Vector3f& factors)
        {
            Transform3D scaling(factors.x, 0, 0, 0,
                                0, factors.y, 0, 0,
                                0, 0, factors.z, 0,
                                0, 0, 0, 1);

            return combine(scaling);
        }

        Transform3D& scale(const sf::Vector3f& factors, const sf::Vector3f& center)
        {
            return scale(factors.x, factors.y, factors.z, center.x, center.y, center.z);
        }


    private:
        float matrix[4][4];
    };
    static const Transform3D Identity;
    Transform3D operator *(const Transform3D& left, const Transform3D& right)
    {
        return Transform3D(left).combine(right);
    }

    Transform3D& operator *=(Transform3D& left, const Transform3D& right)
    {
        return left.combine(right);
    }

    sf::Vector3f operator *(const Transform3D& left, const sf::Vector3f& right)
    {
        return left.transformPoint(right);
    }

    bool operator ==(const Transform3D& left, const Transform3D& right)
    {
        const float* a = left.getMatrix();
        const float* b = right.getMatrix();

        return ((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]) &&
                (a[4] == b[4]) && (a[5] == b[5]) && (a[6] == b[6]) && (a[7] == b[7]) &&
                (a[8] == b[8]) && (a[9] == b[9]) && (a[10] == b[10]) && (a[11] == b[11]) &&
                (a[12] == b[12]) && (a[13] == b[13]) && (a[14] == b[14]) && (a[15] == b[15]));
    }

    bool operator !=(const Transform3D& left, const Transform3D& right)
    {
        return !(left == right);
    }

}