#pragma once
#include <SFML/Window/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "RenderTarget.hpp"

namespace DDD
{
    class RenderWindow3D : public sf::RenderWindow, public RenderTarget3D
    {
    public:
        using RenderWindow::RenderWindow;
        using sf::RenderTarget::clear;
        // using RenderTarget3D::clear;
        using sf::RenderTarget::draw;
        using RenderTarget3D::draw;

        ~RenderWindow3D() = default;

        sf::Vector2u getSize() const override;
    private:
        void onCreate() override;
    };
}