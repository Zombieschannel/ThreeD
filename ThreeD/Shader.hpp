#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <unordered_map>
#include <cstdint>
#include "OpenGL.hpp"
#include "Error.hpp"
#include "Transform.hpp"
#include "ColorF.hpp"
#include "Texture.hpp"

#ifndef GL_COMPUTE_SHADER
    #define GL_COMPUTE_SHADER 0
#endif
#ifndef GL_GEOMETRY_SHADER
    #define GL_GEOMETRY_SHADER 0
#endif
#ifndef GL_TESS_CONTROL_SHADER
    #define GL_TESS_CONTROL_SHADER 0
#endif
#ifndef GL_TESS_EVALUATION_SHADER
    #define GL_TESS_EVALUATION_SHADER 1
#endif
namespace DDD
{
	class Shader3D
	{
    public:
        enum Type
        {
            Vertex = GL_VERTEX_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
            Compute = GL_COMPUTE_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            TessControl = GL_TESS_CONTROL_SHADER,
            TessEvaluation = GL_TESS_EVALUATION_SHADER
        };
    private:
        mutable std::unordered_map<std::string, std::int32_t> uniformLocationCache;
        std::uint32_t ID;
        std::int32_t GetUniformLocation(const std::string& name) const;
    public:
        Shader3D();
        ~Shader3D();
        std::uint32_t getHandle() const;
		bool loadFromFile(const std::string& shaderPath, Type type);
        void loadFromMemory(const std::string& memory, Type type);
		void loadFromStream(sf::InputStream& stream, Type type);
        void setSamplers(std::uint32_t count);
        void setUniform(const std::string& name, const Texture3D& v) const;
        void setUniform(const std::string& name, const Transform3D& v) const;
        void setUniformMat4(const std::string& name, const float* first) const;
        void setUniform(const std::string& name, const float v) const;
        void setUniform(const std::string& name, const std::int32_t v) const;
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