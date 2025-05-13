#include "RenderWindow.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

namespace DDD
{
    RenderWindow3D::RenderWindow3D(sf::VideoMode mode, const sf::String& title, std::uint32_t style, sf::State state, const sf::ContextSettings& settings)
    {
        create(mode, title, style, state, settings);
    }
    RenderWindow3D::RenderWindow3D(sf::WindowHandle handle, const sf::ContextSettings& settings)
    {
        create(handle, settings);
    }
    sf::Vector2u RenderWindow3D::getSize() const
    {
        return sf::Window::getSize();
    }
    bool RenderWindow3D::setActive(bool active)
    {
        return sf::Window::setActive(active);
    }
    void RenderWindow3D::onCreate()
    {
        // RenderTarget::initialize();
        RenderTarget3D::initialize();
    }
}
