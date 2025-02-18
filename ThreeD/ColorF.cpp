#include "ColorF.hpp"

namespace DDD
{
    ColorF::ColorF()
        : r(0.f), g(0.f), b(0.f), a(1.f)
    {
    }
    ColorF::ColorF(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a)
    {
    }
    ColorF::ColorF(const sf::Color &col)
        : r(col.r / 255.f), g(col.g / 255.f), b(col.b / 255.f), a(col.a / 255.f)
    {
    }
    ColorF::ColorF(float rgb)
        : r(rgb), g(rgb), b(rgb), a(1.f)
    {
    }
    ColorF::~ColorF()
    {
    }
    void ColorF::operator=(const sf::Color col)
    {
        r = col.r / 255.f;
        g = col.g / 255.f;
        b = col.b / 255.f;
        a = col.a / 255.f;
    }
    const sf::Color toColor(const ColorF &col)
	{
		return sf::Color(col.r * 255.f, col.g * 255.f, col.b * 255.f, col.a * 255.f);
	}
    const sf::Color toColor(const float r, const float g, const float b, const float a)
	{
		return sf::Color(r * 255.f, g * 255.f, b * 255.f, a * 255.f);
	}
}