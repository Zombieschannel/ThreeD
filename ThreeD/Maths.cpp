#include "Maths.hpp"

namespace DDD
{
	std::array<float, 9> getMat3(const Transform3D& m)
	{
		const float* data = m.getMatrix();
		return {
			data[0], data[1], data[2],
			data[4], data[5], data[6],
			data[8], data[9], data[10]
		};
	}
	std::array<float, 9> getInverseMat3(const std::array<float, 9>& m)
	{
		const float det = m[0] * (m[4] * m[8] - m[5] * m[7]) -
						  m[1] * (m[3] * m[8] - m[5] * m[6]) +
						  m[2] * (m[3] * m[7] - m[4] * m[6]);

		if (det != 0.f)
		{
			return {
				(m[4] * m[8] - m[5] * m[7]) / det,
			   -(m[1] * m[8] - m[2] * m[7]) / det,
				(m[1] * m[5] - m[2] * m[4]) / det,
			   -(m[3] * m[8] - m[5] * m[6]) / det,
				(m[0] * m[8] - m[2] * m[6]) / det,
			   -(m[0] * m[5] - m[2] * m[3]) / det,
				(m[3] * m[7] - m[4] * m[6]) / det,
			   -(m[0] * m[7] - m[1] * m[6]) / det,
				(m[0] * m[4] - m[1] * m[3]) / det
			};
		}

		return std::array{1.f, 0.f, 0.f,
						  0.f, 1.f, 0.f,
						  0.f, 0.f, 1.f};
	}
	std::array<float, 9> getTransposedMat3(const std::array<float, 9>& m)
	{
		return {
			m[0], m[3], m[6],
			m[1], m[4], m[7],
			m[2], m[5], m[8]
		};
	}

    Transform3D lookAt(const sf::Vector3f eye, const sf::Vector3f center, const sf::Vector3f up)
	{
		const sf::Vector3f f((center - eye).normalized());
		const sf::Vector3f s(f.cross(up).normalized());
		const sf::Vector3f u(s.cross(f));

		return Transform3D(
			s.x, s.y, s.z, -s.dot(eye),
			u.x, u.y, u.z, -u.dot(eye),
			-f.x, -f.y, -f.z, f.dot(eye),
			0.f, 0.f, 0.f, 1.f
		);
	}
    sf::Vector3f calculateNormal(const sf::Vector3f point1, const sf::Vector3f point2, const sf::Vector3f point3)
	{
		const sf::Vector3f A = point2 - point1;
		const sf::Vector3f B = point3 - point1;
		sf::Vector3f N;
		N.x = A.y * B.z - A.z * B.y;
		N.y = A.z * B.x - A.x * B.z;
		N.z = A.x * B.y - A.y * B.x;
		return N;
	}
}