#pragma once
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "RenderTarget.hpp"

namespace DDD
{
    class RenderWindow3D : public sf::RenderTarget, public sf::Window, public RenderTarget3D
    {
    public:
        RenderWindow3D();
        RenderWindow3D(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
        RenderWindow3D(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
        virtual ~RenderWindow3D();
        virtual sf::Vector2u getSize() const;
        bool setActive(bool active = true);
        
    protected:
        virtual void onCreate();
        virtual void onResize();
    };
}