#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Window.hpp>
#include "Error.h"
#include "ColorF.h"
namespace DDD
{
	class RenderWindow3D;
	class Texture3D
	{
		friend class FrameBuffer3D;
	public:
		enum Type
		{
#if defined(GLES20)
			TextureRGBA = GL_RGBA, //RGBA8
			SpecularMap = -1, //R8
			HDR = -2, //R8
			Depth = GL_DEPTH_COMPONENT,
			TextureRGB = GL_RGB,
#else
			TextureRGBA = GL_RGBA8, //RGBA8
			SpecularMap = GL_R8, //R8
			HDR = GL_RGBA16F,
			Depth = GL_DEPTH_COMPONENT,
			TextureRGB = GL_RGB8,
#endif
		};
	private:
		unsigned int ID = 0U;
		unsigned int slot = 0U;
		mutable bool flipped = 0;
		Type type = TextureRGBA;
		bool isSmooth = 0;
		bool hasMipmap = 0;
		bool isRepeated = 0;
		ColorF borderColor;
		sf::Vector2u size = sf::Vector2u();
		int bytesPerPixel() const
		{
			switch (type)
			{
			case DDD::Texture3D::TextureRGBA:
				return 4;
			case DDD::Texture3D::SpecularMap:
				return 1;
			case DDD::Texture3D::HDR:
				return 8;
			case DDD::Texture3D::Depth:
				return 4;
			case DDD::Texture3D::TextureRGB:
				return 3;
			default:
				break;
			}
		}
	public:
		Texture3D()
		{
		}
		Texture3D(unsigned int _ID, unsigned int _slot, Type _type)
			: ID(_ID), slot(_slot), type(_type)
		{
		}
		~Texture3D()
		{
			if (ID)
			{
				GLCall(glDeleteTextures(1, &ID));
			}
		}
		const unsigned int& getHandle() const
		{
			return ID;
		}
		void create(unsigned int x, unsigned int y, Type type = Type::TextureRGBA)
		{
			create(sf::Vector2u(x, y), type);
		}
		void create(sf::Vector2u size, Type type = Type::TextureRGBA)
		{
			if (size == sf::Vector2u())
			{
				sf::err() << "Cannot create empty texture.\n";
				return;
			}
			this->type = type;
			if (ID)
			{
				GLCall(glDeleteTextures(1, &ID));
			}
			this->size = size;
			GLCall(glGenTextures(1, &ID));
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, isSmooth ? GL_LINEAR : GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, isSmooth ? GL_LINEAR : GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));

			if (type != Type::Depth)
			{
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, type, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
			}
			else
			{
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, type, size.x, size.y, 0, type, GL_FLOAT, NULL));
			}
			hasMipmap = 0;

			flipped = 0;
		}

		void setBorderColor(const ColorF& color)
		{
			if (!ID)
				return;
			this->borderColor = color;
#if not __ANDROID__
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &this->borderColor.r));
#endif
		}
		bool loadFromImage(sf::Image& image, Type type = Type::TextureRGBA)
		{
			this->type = type;
			if (ID)
			{
				GLCall(glDeleteTextures(1, &ID));
			}
			GLCall(glGenTextures(1, &ID));
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, isSmooth ? GL_LINEAR : GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, isSmooth ? GL_LINEAR : GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));

			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, type, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()));
			size = image.getSize();
			flipped = 0;
			hasMipmap = 0;

			return 1;
		}
		bool loadFromFile(const std::string filePath, Type type = Type::TextureRGBA)
		{
			sf::Image image;
			if (!image.loadFromFile(filePath))
				return 0;
			loadFromImage(image, type);
			return 1;
		}
		void generateMipMap()
		{
			if (!ID)
				return;
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
			GLCall(glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_MIN_FILTER,
				isSmooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
			hasMipmap = 1;
		}
		void setSmooth(bool smooth)
		{
			if (!ID)
				return;
			isSmooth = smooth;
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, isSmooth ? GL_LINEAR : GL_NEAREST));
			if (hasMipmap)
			{
				GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, isSmooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
			}
			else
			{
				GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, isSmooth ? GL_LINEAR : GL_NEAREST));
			}

		}
		void loadFromWindow(const sf::Window& window, const sf::Vector2u offset = sf::Vector2u())
		{
			if (!ID)
				return;
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glCopyTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, 0, 0, window.getSize().x, window.getSize().y));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, isSmooth ? GL_LINEAR : GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
			hasMipmap = 0;
			flipped = 1;
		}
		const bool& getSmooth() const
		{
			return isSmooth;
		}
		void copyToImage(sf::Image& img) const
		{
			if (!ID)
				return;

			sf::Uint8* pixels = new sf::Uint8[getSize().x * getSize().y * bytesPerPixel()];
#if __ANDROID__
			//fix for gles

#else
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels));
#endif

			img.create(getSize().x, getSize().y, pixels);
			if (flipped)
				img.flipVertically();

			delete[] pixels;
		}
		void setRepeated(bool repeated)
		{
			if (!ID)
				return;
			isRepeated = repeated;
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
		}

		
		const bool& getRepeated() const
		{
			return isRepeated;
		}

		const sf::Vector2u& getSize() const
		{
			return size;
		}
		void setSize(const sf::Vector2u& size)
		{
			this->size = size;
		}
		void setSlot(unsigned int slot)
		{
			this->slot = slot;
		}
		unsigned int getSlot() const
		{
			return slot;
		}

		static void Bind(const Texture3D* texture)
		{
			if (texture)
			{
				GLCall(glActiveTexture(GL_TEXTURE0 + texture->slot));
				GLCall(glBindTexture(GL_TEXTURE_2D, texture->ID));
			}
			else
			{
				GLCall(glActiveTexture(GL_TEXTURE0));
				GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			}
		}
	};
}