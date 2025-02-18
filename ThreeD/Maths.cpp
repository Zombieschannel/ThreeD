#include "Maths.hpp"

namespace DDD
{
    const float dot(const sf::Vector3f vec1, const sf::Vector3f vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

    const float dot(const sf::Vector2f vec1, const sf::Vector2f vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

    const sf::Vector3f cross(const sf::Vector3f vec1, const sf::Vector3f vec2)
	{
		return sf::Vector3f(vec1.y * vec2.z - vec1.z * vec2.y, 
							vec1.z * vec2.x - vec1.x * vec2.z,
							vec1.x * vec2.y - vec1.y * vec2.x);
	}

    const float length(const sf::Vector3f vec1)
	{
		return std::sqrt(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
	}

    const float length(const sf::Vector2f vec1)
	{
		return std::sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
	}

    const sf::Vector3f normalize(const sf::Vector3f vec1)
	{
		float len = length(vec1);
		if (len == 0.f)
			return sf::Vector3f();
		return sf::Vector3f(vec1.x / len, vec1.y / len, vec1.z / len);
	}

    const sf::Vector2f normalize(const sf::Vector2f vec1)
	{
		float len = length(vec1);
		if (len == 0.f)
			return sf::Vector2f();
		return sf::Vector2f(vec1.x / len, vec1.y / len);
	}

    const Transform3D lookAt(const sf::Vector3f eye, const sf::Vector3f center, const sf::Vector3f up)
	{
		sf::Vector3f f(normalize(center - eye));
		sf::Vector3f s(normalize(cross(f, up)));
		sf::Vector3f u(cross(s, f));

		return Transform3D(
			s.x, s.y, s.z, -dot(s, eye),
			u.x, u.y, u.z, -dot(u, eye),
			-f.x, -f.y, -f.z, dot(f, eye),
			0.f, 0.f, 0.f, 1.f
		);
	}
    const sf::Vector3f calculateNormal(const sf::Vector3f point1, const sf::Vector3f point2, const sf::Vector3f point3)
	{
		sf::Vector3f A = point2 - point1;
		sf::Vector3f B = point3 - point1;
		sf::Vector3f N;
		N.x = A.y * B.z - A.z * B.y;
		N.y = A.z * B.x - A.x * B.z;
		N.z = A.x * B.y - A.y * B.x;
		return N;
	}
}