#pragma once
#include "OGL.h"
#include <iostream>
#include "Error.h"
#include "Transform.h"
#include <unordered_map>
#include "ColorF.h"
#include "Texture.h"
#include "Light.h"
namespace DDD
{
	class Shader3D
	{
    public:
        enum Type
        {
            Vertex = GL_VERTEX_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
#if defined(GLES31) || defined(GLES32) || not defined(__ANDROID__)
            Compute = GL_COMPUTE_SHADER,
#endif
#if not defined (__ANDROID__)
            Geometry = GL_GEOMETRY_SHADER,
            TessControl = GL_TESS_CONTROL_SHADER,
            TessEvaluation = GL_TESS_EVALUATION_SHADER
#endif
        };
    private:
        mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
        unsigned int shaderProgram = 0;
        unsigned int CompileShader(unsigned int type, const std::string& source)
        {
            GLCall(unsigned int id = glCreateShader(type));
            const char* src = source.c_str();
            GLCall(glShaderSource(id, 1, &src, nullptr));
            GLCall(glCompileShader(id));
            int result;
            GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
            if (result == GL_FALSE)
            {
                int length;
                GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
                char* message = (char*)alloca(length * sizeof(char));
                GLCall(glGetShaderInfoLog(id, length, &length, message));
                sf::err() << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
                sf::err() << message << std::endl;
                GLCall(glDeleteShader(id));
                return 0;
            }
            return id;
        }
        int GetUniformLocation(const std::string& name) const
        {
            if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
                return m_UniformLocationCache[name];
            GLCall(int location = glGetUniformLocation(shaderProgram, name.c_str()));
            if (location == -1)
                std::cout << "Uniform " << name << " not found!" << std::endl;
            m_UniformLocationCache[name] = location;
            return location;
        }
    public:
        ~Shader3D()
        {
            glDeleteProgram(shaderProgram);
        }
		bool loadFromFile(const std::string& shaderPath, Type type)
		{
            sf::FileInputStream stream;
            if (!stream.open(shaderPath))
            {
                std::cout << "Could not open shader!" << std::endl;
                return 0;
            }
            loadFromStream(stream, type);
            return 1;
		}
        void loadFromMemory(const std::string& memory, Type type)
        {
            sf::MemoryInputStream stream;
            stream.open(memory.c_str(), memory.size());
            loadFromStream(stream, type);
        }
		void loadFromStream(sf::InputStream& stream, Type type)
		{
            std::string tmp;
            tmp.resize(stream.getSize());
            stream.read(&tmp[0], stream.getSize());
            unsigned int program = shaderProgram;
            if (!shaderProgram)
            {
                GLCall(program = glCreateProgram());
            }

            unsigned int s = CompileShader(type, tmp);
            GLCall(glAttachShader(program, s));
            GLCall(glLinkProgram(program));
            GLCall(glValidateProgram(program));
            GLCall(glDeleteShader(s));
            shaderProgram = program;
		}
        static void Bind(const Shader3D* shader)
        {
            if (shader)
            {
                GLCall(glUseProgram(shader->shaderProgram));
            }
            else
            {
                GLCall(glUseProgram(0));
            }
        }
        void setSamplers(unsigned int count)
        {
            int loc = GetUniformLocation("u_textures");
            int* samplers = new int[count];
            for (int i = 0; i < count; i++)
                samplers[i] = i;
            GLCall(glUniform1iv(loc, count, samplers));
            delete[] samplers;
        }
        void setUniform(const std::string& name, const Texture3D& v) const
        {
            GLCall(glUniform1i(GetUniformLocation(name), v.getSlot()));
        }
        void setUniform(const std::string& name, const Transform3D& v) const
        {
#ifdef GLES20
            GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, v.transpose().getMatrix()));
#else
            GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, v.getMatrix()));
#endif
        }
        void setUniformMat4(const std::string& name, const float* first) const
        {
            GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, first));
        }
        void setUniform(const std::string& name, const float v) const
        {
            GLCall(glUniform1f(GetUniformLocation(name), v));
        }
        void setUniform(const std::string& name, const int v) const
        {
            GLCall(glUniform1i(GetUniformLocation(name), v));
        }
        void setUniform(const std::string& name, const sf::Color& v) const
        {
            GLCall(glUniform4f(GetUniformLocation(name), v.r / 255.f, v.g / 255.f, v.b / 255.f, v.a / 255.f));
        }
        void setUniform(const std::string& name, const ColorF& v) const
        {
            GLCall(glUniform4f(GetUniformLocation(name), v.r, v.g, v.b, v.a));
        }
        void setUniform(const std::string& name, const sf::Vector3f& v) const
        {
            GLCall(glUniform3f(GetUniformLocation(name), v.x, v.y, v.z));
        }
        void setUniformArray(const std::string& name, std::vector<float> arr) const
        {
            GLCall(glUniform1fv(GetUniformLocation(name), arr.size(), arr.data()));
        }
        void setUniform(const Light3D& light, const int index) const
        {
            light.setUniforms(this, index);
        }
	};
}