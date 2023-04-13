#pragma once
#include <SFML/Graphics/Color.hpp>
namespace DDD
{
	class ColorF
	{
	public:
		float r, g, b, a;
		ColorF()
			: r(0.f), g(0.f), b(0.f), a(0.f)
		{

		}
		ColorF(float r, float g, float b, float a = 1.f)
			: r(r), g(g), b(b), a(a)
		{

		}
		ColorF(const sf::Color& col)
			: r(col.r / 255.f), g(col.g / 255.f), b(col.b / 255.f), a(col.a / 255.f)
		{

		}
		ColorF(float rgb)
			: r(rgb), g(rgb), b(rgb), a(1.f)
		{

		}
		~ColorF()
		{

		}
		static sf::Color toColor(const ColorF& col)
		{
			return sf::Color(col.r * 255.f, col.g * 255.f, col.b * 255.f, col.a * 255.f);
		}
		static ColorF toColorF(const sf::Color& col)
		{
			return ColorF(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
		}
		static sf::Color toColor(const float r, const float g, const float b, const float a)
		{
			return sf::Color(r * 255.f, g * 255.f, b * 255.f, a * 255.f);
		}
		static ColorF toColorF(const float r, const float g, const float b, const float a)
		{
			return ColorF(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
		}
	};
}