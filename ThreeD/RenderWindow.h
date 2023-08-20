#pragma once
#include "RenderTarget.h"
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
namespace DDD
{
    class RenderWindow3D : public sf::RenderTarget, public sf::Window, public RenderTarget3D
    {
    public:
        RenderWindow3D()
        {
            
        }
        RenderWindow3D(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings())
        {
            create(mode, title, style, settings);
        }
        RenderWindow3D(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings())
        {
            create(handle, settings);
        }
        virtual ~RenderWindow3D()
        {

        }
        virtual sf::Vector2u getSize() const
        {
            return sf::Window::getSize();
        }
        bool setActive(bool active = true)
        {
            bool result = sf::Window::setActive(active);

            if (result)
                sf::RenderTarget::setActive(active);
            return result;
        }
    protected:

        virtual void onCreate()
        {
            sf::RenderTarget::initialize();
        }
        virtual void onResize()
        {
            setView(getView());
        }
    };
}