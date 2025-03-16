#include "RenderWindow.hpp"

namespace DDD
{
    RenderWindow3D::RenderWindow3D()
    {
                
    }
    RenderWindow3D::RenderWindow3D(sf::VideoMode mode, const sf::String& title, std::uint32_t style, sf::State state, const sf::ContextSettings& settings)
    {
        create(mode, title, style, state, settings);
    }
    RenderWindow3D::RenderWindow3D(sf::WindowHandle handle, const sf::ContextSettings& settings)
    {
        create(handle, settings);
    }
    RenderWindow3D::~RenderWindow3D()
    {

    }
    sf::Vector2u RenderWindow3D::getSize() const
    {
        return sf::Window::getSize();
    }
    bool RenderWindow3D::setActive(bool active)
    {
        bool result = sf::Window::setActive(active);
        return result;
    }
}