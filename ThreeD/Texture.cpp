#include "Texture.hpp"

namespace
{
    int typeToGLsize(DDD::Texture3D::Type type)
    {
        switch (type)
        {
        case DDD::Texture3D::TextureRGBA:
            return 4;
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
}


namespace DDD
{
    Texture3D::Texture3D()
        : ID(0U), slot(0U), flipped(false), type(TextureRGBA), smooth(false), hasMipmap(false), repeated(false), size(0, 0)
    {

    }
    Texture3D::Texture3D(std::uint32_t ID, std::uint32_t slot, Type type)
        : ID(ID), slot(slot), flipped(false), type(type), smooth(false), hasMipmap(false), repeated(false), size(0, 0)
    {

    }
    Texture3D::~Texture3D()
    {
        if (ID)
        {
            GLCall(glDeleteTextures(1, &ID));
        }
    }
    std::uint32_t Texture3D::getHandle() const
    {
        return ID;
    }
    void Texture3D::create(sf::Vector2u size, Type type)
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
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));

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
    bool Texture3D::loadFromImage(const sf::Image &image, Type type)
    {
        this->type = type;
        if (ID)
        {
            GLCall(glDeleteTextures(1, &ID));
        }
        GLCall(glGenTextures(1, &ID));
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, type, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()));
        size = image.getSize();
        flipped = 0;
        hasMipmap = 0;

        return 1;
    }
    bool Texture3D::loadFromFile(const std::string& filePath, Type type)
    {
        sf::Image image;
        if (!image.loadFromFile(filePath))
            return 0;
        loadFromImage(image, type);
        return 1;
    }
    void Texture3D::generateMipMap()
    {
        if (!ID)
            return;
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        GLCall(glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            smooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
        hasMipmap = 1;
    }
    void Texture3D::setSmooth(bool smooth)
    {
        if (!ID)
            return;
        this->smooth = smooth;
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
        if (hasMipmap)
        {
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR));
        }
        else
        {
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
        }

    }
    void Texture3D::update(const sf::Window &window, const sf::Vector2u offset)
    {
        if (!ID)
            return;
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));
        GLCall(glCopyTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, 0, 0, window.getSize().x, window.getSize().y));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
        hasMipmap = 0;
        flipped = 1;
    }
    const bool Texture3D::isSmooth() const
    {
        return smooth;
    }
    void Texture3D::copyToImage(sf::Image& img) const
    {
        if (!ID)
            return;

        sf::Uint8* pixels = new sf::Uint8[getSize().x * getSize().y * typeToGLsize(type)];
#ifdef SFML_OPENGL_ES
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
    void Texture3D::setRepeated(bool repeated)
    {
        if (!ID)
            return;
        this->repeated = repeated;
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, ID));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
    }
    const bool Texture3D::isRepeated() const
    {
        return repeated;
    }
    const sf::Vector2u Texture3D::getSize() const
    {
        return size;
    }
    void Texture3D::setSize(const sf::Vector2u size)
    {
        this->size = size;
    }
    void Texture3D::setSlot(std::uint32_t slot)
    {
        this->slot = slot;
    }
    const std::uint32_t Texture3D::getSlot() const
    {
        return slot;
    }
    void BindTexture(const Texture3D *texture)
	{
		if (texture)
		{
			GLCall(glActiveTexture(GL_TEXTURE0 + texture->getSlot()));
			GLCall(glBindTexture(GL_TEXTURE_2D, texture->getHandle()));
		}
		else
		{
			GLCall(glActiveTexture(GL_TEXTURE0));
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}
}