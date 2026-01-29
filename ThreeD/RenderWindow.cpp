#include "RenderWindow.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

namespace DDD
{
    sf::Vector2u RenderWindow3D::getSize() const
    {
        return sf::Window::getSize();
    }
    void RenderWindow3D::onCreate()
    {
        RenderWindow::onCreate();
        RenderTarget3D::initialize();
    }
}
