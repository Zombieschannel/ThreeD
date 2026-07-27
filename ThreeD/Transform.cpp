#include "Transform.hpp"

namespace DDD
{
    const Transform3D Transform3D::Identity;

    Transform3D::Transform3D() { }
    Transform3D::Transform3D(const float a00, const float a01, const float a02, const float a03,
                             const float a10, const float a11, const float a12, const float a13,
                             const float a20, const float a21, const float a22, const float a23,
                             const float a30, const float a31, const float a32, const float a33)
        : matrix{ a00, a10, a20, a30,
                  a01, a11, a21, a31,
                  a02, a12, a22, a32,
                  a03, a13, a23, a33 }
    {

    }
    const float *Transform3D::getMatrix() const
    {
        return &matrix[0];
    }
    sf::Vector3f Transform3D::transformPoint(const sf::Vector3f point) const
    {
        return sf::Vector3f(matrix[0] * point.x + matrix[1] * point.y + matrix[2] * point.z + matrix[3],
                            matrix[4] * point.x + matrix[5] * point.y + matrix[6] * point.z + matrix[7],
                            matrix[8] * point.x + matrix[9] * point.y + matrix[10] * point.z + matrix[11]);
    }
    Transform3D Transform3D::transpose() const
    {
        return Transform3D(
                matrix[0], matrix[4],matrix[8],matrix[12],
                matrix[1], matrix[5],matrix[9],matrix[13],
                matrix[2], matrix[6],matrix[10],matrix[14],
                matrix[3], matrix[7],matrix[11],matrix[15]
        );
    }
    Transform3D Transform3D::Perspective(const sf::Angle fov, const float aspect, const float near, const float far)
    {
        const float tanHalfFovY = tan(fov.asRadians() / 2);
        const float a = 1 / (aspect * tanHalfFovY);
        const float b = 1 / tanHalfFovY;
        const float c = -(far + near) / (far - near);
        const float d = -(2 * far * near) / (far - near);

        return Transform3D(a, 0, 0, 0,
                           0, b, 0, 0,
                           0, 0, c, d,
                           0, 0, -1, 0);
    }
    Transform3D Transform3D::Ortho(const float left, const float right, const float top, const float bottom, const float near, const float far)
    {
        const float tx = -(right + left) / (right - left);
        const float ty = -(top + bottom) / (top - bottom);
        const float tz = -(far + near) / (far - near);

        const float a = 2 / (right - left);
        const float b = 2 / (top - bottom);
        const float c = -2 / (far - near);

        return Transform3D(a, 0, 0, tx,
                           0, b, 0, ty,
                           0, 0, c, tz,
                           0, 0, 0, 1);
    }
    Transform3D& Transform3D::combine(const Transform3D& transform)
    {
        Transform3D newTransform;
        for (std::uint8_t i = 0; i < 4; i++)
        {
            for (std::uint8_t j = 0; j < 4; j++)
            {
                float sumElements = 0.f;
                for (std::uint8_t k = 0; k < 4; k++)
                    sumElements += this->matrix.at(k * 4 + j) * transform.matrix.at(i * 4 + k);
                newTransform.matrix.at(i * 4 + j) = sumElements;
            }
        }
        *this = newTransform;
        return *this;
    }
    Transform3D& Transform3D::translate(const sf::Vector3f offset)
    {
        const Transform3D translation(1, 0, 0, offset.x,
                                      0, 1, 0, offset.y,
                                      0, 0, 1, offset.z,
                                      0, 0, 0, 1);

        return combine(translation);
    }
    Transform3D& Transform3D::rotate(const sf::Vector3f angle)
    {
        const float radX = angle.x * 3.141592654f / 180.f;
        const float cosX = std::cosf(radX);
        const float sinX = std::sinf(radX);
        const Transform3D rotationX(  1,  0,      0, 0,
                                      0, cosX, -sinX, 0,
                                      0, sinX, cosX, 0,
                                      0,  0,      0, 1);

        const float radY = angle.y * 3.141592654f / 180.f;
        const float cosY = std::cosf(radY);
        const float sinY = std::sinf(radY);

        const Transform3D rotationY(cosY, 0, sinY, 0,
                                    0, 1, 0, 0,
                                    -sinY, 0, cosY, 0,
                                    0, 0, 0, 1);

        const float radZ = angle.z * 3.141592654f / 180.f;
        const float cosZ = std::cosf(radZ);
        const float sinZ = std::sinf(radZ);

        const Transform3D rotationZ(cosZ, -sinZ, 0, 0,
                                    sinZ, cosZ, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1);


        return combine(rotationX).combine(rotationY).combine(rotationZ);
    }
    Transform3D& Transform3D::scale(const sf::Vector3f factors)
    {
        const Transform3D scaling(factors.x, 0, 0, 0,
                                0, factors.y, 0, 0,
                                0, 0, factors.z, 0,
                                0, 0, 0, 1);

        return combine(scaling);
    }
    Transform3D& Transform3D::scale(const sf::Vector3f factors, const sf::Vector3f center)
    {
        const Transform3D scaling(factors.x, 0, 0, center.x * (1 - factors.x),
                                0, factors.y, 0, center.y * (1 - factors.y),
                                0, 0, factors.z, center.z * (1 - factors.z),
                                0, 0, 0, 1);

        return combine(scaling);
    }
    Transform3D operator*(const Transform3D& left, const Transform3D& right)
    {
        return Transform3D(left).combine(right);
    }
    Transform3D& operator*=(Transform3D& left, const Transform3D& right)
    {
        return left.combine(right);
    }
    sf::Vector3f operator*(const Transform3D& left, const sf::Vector3f right)
    {
        return left.transformPoint(right);
    }
    bool operator==(const Transform3D& left, const Transform3D& right)
    {
        const float* a = left.getMatrix();
        const float* b = right.getMatrix();

        return ((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]) &&
                (a[4] == b[4]) && (a[5] == b[5]) && (a[6] == b[6]) && (a[7] == b[7]) &&
                (a[8] == b[8]) && (a[9] == b[9]) && (a[10] == b[10]) && (a[11] == b[11]) &&
                (a[12] == b[12]) && (a[13] == b[13]) && (a[14] == b[14]) && (a[15] == b[15]));
    }
    bool operator!=(const Transform3D& left, const Transform3D& right)
    {
        return !(left == right);
    }
}