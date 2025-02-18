#include "Shader.hpp"

namespace DDD
{
    std::int32_t Shader3D::GetUniformLocation(const std::string& name) const
    {
        if (uniformLocationCache.find(name) != uniformLocationCache.end())
            return uniformLocationCache[name];

        GLCall(std::int32_t location = glGetUniformLocation(ID, name.c_str()));

        if (location == -1)
            std::cout << "Uniform " << name << " not found!" << std::endl;

        uniformLocationCache[name] = location;
        return location;
    }
    Shader3D::Shader3D()
        : ID(0)
    {
        GLCall(ID = glCreateProgram());
    }
    Shader3D::~Shader3D()
    {
        GLCall(glDeleteProgram(ID));
    }
    std::uint32_t Shader3D::getHandle() const
    {
        return ID;
    }
    bool Shader3D::loadFromFile(const std::string &shaderPath, Type type)
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
    void Shader3D::loadFromMemory(const std::string& memory, Type type)
    {
        sf::MemoryInputStream stream;
        stream.open(memory.c_str(), memory.size());
        loadFromStream(stream, type);
    }
    void Shader3D::loadFromStream(sf::InputStream& stream, Type type)
    {
        std::string tmp;
        tmp.resize(stream.getSize());
        stream.read(&tmp[0], stream.getSize());

        GLCall(std::uint32_t shader = glCreateShader(type));

        const char* data = tmp.data();
        GLCall(glShaderSource(ID, 1, &data, nullptr));
        GLCall(glCompileShader(ID));

        std::int32_t result = 0;
        GLCall(glGetShaderiv(ID, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE)
        {
            std::int32_t length;
            GLCall(glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length));

            std::string message;
            message.resize(length);

            GLCall(glGetShaderInfoLog(ID, length, &length, &message[0]));
            sf::err() << "Failed to compile shader!" << std::endl;
            sf::err() << message << std::endl;
            GLCall(glDeleteShader(ID));
            return;
        }

        GLCall(glAttachShader(ID, shader));
        GLCall(glLinkProgram(ID));

        result = 0;
        GLCall(glGetProgramiv(ID, GL_LINK_STATUS, &result));
        if (result == GL_FALSE)
        {
            std::int32_t length;
            GLCall(glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &length));

            std::string message;
            message.resize(length);

            GLCall(glGetShaderInfoLog(ID, length, &length, &message[0]));
            sf::err() << "Failed to link shader!" << std::endl;
            sf::err() << message << std::endl;
            GLCall(glDeleteShader(shader));
            return;
        }

        GLCall(glValidateProgram(ID));

        int validateResult;
        GLCall(glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateResult));
        if (validateResult == GL_FALSE)
        {
            std::int32_t length;
            GLCall(glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &length));

            std::string message;
            message.resize(length);

            GLCall(glGetProgramInfoLog(ID, length, &length, &message[0]));
            sf::err() << "Failed to validate program!" << std::endl;
            sf::err() << message << std::endl;
            GLCall(glDeleteShader(shader));
            return;
        }

        GLCall(glDeleteShader(shader));
    }
    void Shader3D::setSamplers(std::uint32_t count)
    {
        std::int32_t loc = GetUniformLocation("u_textures");
        std::int32_t* samplers = new std::int32_t[count];
        for (std::int32_t i = 0; i < count; i++)
            samplers[i] = i;
        GLCall(glUniform1iv(loc, count, samplers));
        delete[] samplers;
    }
    void Shader3D::setUniform(const std::string& name, const Texture3D& v) const
    {
        GLCall(glUniform1i(GetUniformLocation(name), v.getSlot()));
    }
    void Shader3D::setUniform(const std::string& name, const Transform3D& v) const
    {
#ifdef GLES20
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, v.transpose().getMatrix()));
#else
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, v.getMatrix()));
#endif
    }
    void Shader3D::setUniformMat4(const std::string& name, const float *first) const
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, first));
    }
    void Shader3D::setUniform(const std::string& name, const float v) const
    {
        GLCall(glUniform1f(GetUniformLocation(name), v));
    }
    void Shader3D::setUniform(const std::string& name, const std::int32_t v) const
    {
        GLCall(glUniform1i(GetUniformLocation(name), v));
    }
    void Shader3D::setUniform(const std::string& name, const sf::Color& v) const
    {
        GLCall(glUniform4f(GetUniformLocation(name), v.r / 255.f, v.g / 255.f, v.b / 255.f, v.a / 255.f));
    }
    void Shader3D::setUniform(const std::string& name, const ColorF& v) const
    {
        GLCall(glUniform4f(GetUniformLocation(name), v.r, v.g, v.b, v.a));
    }
    void Shader3D::setUniform(const std::string& name, const sf::Vector3f& v) const
    {
        GLCall(glUniform3f(GetUniformLocation(name), v.x, v.y, v.z));
    }
    void Shader3D::setUniform(const std::string& name, const sf::Vector3i& v) const
    {
        GLCall(glUniform3i(GetUniformLocation(name), v.x, v.y, v.z));
    }
    void Shader3D::setUniform(const std::string& name, const sf::Vector2f& v) const
    {
        GLCall(glUniform2f(GetUniformLocation(name), v.x, v.y));
    }
    void Shader3D::setUniform(const std::string& name, const sf::Vector2i& v) const
    {
        GLCall(glUniform2i(GetUniformLocation(name), v.x, v.y));
    }
    void Shader3D::setUniformArray(const std::string &name, const std::vector<float> &arr) const
    {
        GLCall(glUniform1fv(GetUniformLocation(name), arr.size(), arr.data()));
    }
    void BindShader(const Shader3D *shader)
    {
        if (shader)
        {
            GLCall(glUseProgram(shader->getHandle()));
        }
        else
        {
            GLCall(glUseProgram(0));
        }
    }
}