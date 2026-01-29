#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdint>
#include "Error.hpp"
#include "ColorF.hpp"

#ifndef GL_RGBA16F
	#define GL_RGBA16F -1
#endif

namespace DDD
{
	class RenderWindow3D;
	class Texture3D : public sf::GlResource
	{
		friend class FrameBuffer3D;
	public:
		enum Type
		{
			TextureRGBA = GL_RGBA,
			HDR = GL_RGBA16F,
			Depth = GL_DEPTH_COMPONENT,
			TextureRGB = GL_RGB,
		};
	private:
		std::uint32_t ID;
		mutable bool flipped;
		Type type = TextureRGBA;
		bool smooth;
		bool hasMipmap;
		bool repeated;
		sf::Vector2u size;
	public:
		Texture3D();
		Texture3D(std::uint32_t ID, std::uint32_t slot, Type type);
		~Texture3D();
		
		std::uint32_t getHandle() const;
		const sf::Vector2u getSize() const;
		const bool isSmooth() const;
		const bool isRepeated() const;
		void copyToImage(sf::Image& img) const;

		void create(sf::Vector2u size, Type type = Type::TextureRGBA);
		bool loadFromImage(const sf::Image& image, Type type = Type::TextureRGBA);
		bool loadFromFile(const std::string& filePath, Type type = Type::TextureRGBA);
		void generateMipMap();
		void update(const sf::Window& window, const sf::Vector2u offset = sf::Vector2u());
		
		void setSize(const sf::Vector2u size);
		void setSmooth(bool smooth);
		void setRepeated(bool repeated);
	};
	void TextureSlot(const std::uint8_t slot);
	void BindTexture(const Texture3D* texture);
}