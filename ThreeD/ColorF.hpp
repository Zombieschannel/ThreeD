#pragma once
#include <SFML/Graphics/Color.hpp>

namespace DDD
{
	class ColorF
	{
	public:
		float r, g, b, a;

		ColorF();
		ColorF(float r, float g, float b, float a = 1.f);
		ColorF(const sf::Color& col);
		ColorF(float rgb);
		~ColorF();

		void operator=(const sf::Color col);
	};
	static const sf::Color toColor(const ColorF& col);
	static const sf::Color toColor(const float r, const float g, const float b, const float a = 1.f);
}