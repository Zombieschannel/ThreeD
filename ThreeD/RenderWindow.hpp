#pragma once
#include <SFML/Window/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "RenderTarget.hpp"

namespace DDD
{
    class RenderWindow3D : public sf::Window, public RenderTarget3D
    {
    public:
        RenderWindow3D();
        RenderWindow3D(sf::VideoMode mode, const sf::String& title, std::uint32_t style = sf::Style::Default, sf::State state = sf::State::Windowed, const sf::ContextSettings& settings = sf::ContextSettings());
        RenderWindow3D(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
        ~RenderWindow3D();

        virtual sf::Vector2u getSize() const;
        bool setActive(bool active = true);
    };
}