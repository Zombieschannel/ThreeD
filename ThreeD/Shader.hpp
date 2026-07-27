#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System.hpp>
#include "Transform.hpp"
#include "ColorF.hpp"
#include "Texture.hpp"
#include <unordered_map>
#include <filesystem>


namespace DDD
{
	class Shader3D : public sf::GlResource
	{
	    friend class RenderTarget3D;
    public:
        enum Type
        {
            Vertex,
            Fragment,
            Geometry,
        };
    private:
        mutable std::unordered_map<std::string, std::int32_t> uniformLocationCache;
        std::uint32_t m_program;
        std::int32_t GetUniformLocation(const std::string& name) const;
    public:
        Shader3D();
        ~Shader3D();
        std::uint32_t getHandle() const;
		bool loadFromFile(const std::filesystem::path& path, Type type);
        void loadFromMemory(const void* data, std::uint32_t size, Type type);
		void loadFromStream(sf::InputStream& stream, Type type);
	    static const Shader3D& getDefaultShader();
	    static const Shader3D& getDefaultTexShader();
        void setSamplers(std::uint32_t count) const;
        void setUniform(const std::string& name, const Texture3D& v) const;
        void setUniform(const std::string& name, const Transform3D& v) const;
        void setUniformMat3(const std::string& name, const float* first) const;
        void setUniformMat4(const std::string& name, const float* first) const;
        void setUniform(const std::string& name, float v) const;
        void setUniform(const std::string& name, std::int32_t v) const;
        void setUniform(const std::string& name, const sf::Color& v) const;
        void setUniform(const std::string& name, const ColorF& v) const;
        void setUniform(const std::string& name, const sf::Vector3f& v) const;
        void setUniform(const std::string& name, const sf::Vector3i& v) const;
        void setUniform(const std::string& name, const sf::Vector2f& v) const;
        void setUniform(const std::string& name, const sf::Vector2i& v) const;
        void setUniformArray(const std::string& name, const std::vector<float>& arr) const;
	};
    void BindShader(const Shader3D* shader);
}
