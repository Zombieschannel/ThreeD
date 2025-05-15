#include "Shader.hpp"

namespace DDD
{
    std::int32_t Shader3D::GetUniformLocation(const std::string& name) const
    {
        if (uniformLocationCache.find(name) != uniformLocationCache.end())
            return uniformLocationCache[name];

        GLCall(std::int32_t location = glGetUniformLocation(m_program, name.c_str()));

        if (location == -1)
            sf::err() << "Uniform " << name << " not found!" << std::endl;

        uniformLocationCache[name] = location;
        return location;
    }
    Shader3D::Shader3D()
        : m_program(0)
    {
    }
    Shader3D::~Shader3D()
    {
        if (m_program)
        {
            GLCall(glDeleteProgram(m_program));
        }
    }
    std::uint32_t Shader3D::getHandle() const
    {
        return m_program;
    }
    bool Shader3D::loadFromFile(const std::string &shaderPath, Type type)
    {
        sf::FileInputStream stream;
        if (!stream.open(shaderPath))
        {
            sf::err() << "Could not open shader!" << std::endl;
            return false;
        }
        loadFromStream(stream, type);
        return true;
    }
    void Shader3D::loadFromMemory(const std::string& memory, Type type)
    {
        sf::MemoryInputStream stream(memory.c_str(), memory.size());
        loadFromStream(stream, type);
    }
    void Shader3D::loadFromStream(sf::InputStream& stream, Type type)
    {
        std::string tmp;
        tmp.resize(*stream.getSize());
        stream.read(&tmp[0], *stream.getSize());

        if (!m_program)
        {
            GLCall(m_program = glCreateProgram());
        }

        GLCall(std::uint32_t shader = glCreateShader(type));

        const char* data = &tmp[0];
        GLCall(glShaderSource(shader, 1, &data, nullptr));
        GLCall(glCompileShader(shader));

        std::int32_t result = 0;
        GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE)
        {
            std::int32_t length;
            GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

            std::string message;
            message.resize(length);

            GLCall(glGetShaderInfoLog(shader, length, &length, &message[0]));
            sf::err() << "Failed to compile shader!" << std::endl;
            sf::err() << message << std::endl;
            GLCall(glDeleteShader(shader));
            return;
        }

        GLCall(glAttachShader(m_program, shader));
        GLCall(glLinkProgram(m_program));

        result = 0;
        GLCall(glGetProgramiv(m_program, GL_LINK_STATUS, &result));
        if (result == GL_FALSE)
        {
            std::int32_t length;
            GLCall(glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length));

            std::string message;
            message.resize(length);

            GLCall(glGetShaderInfoLog(m_program, length, &length, &message[0]));
            sf::err() << "Failed to link shader!" << std::endl;
            sf::err() << message << std::endl;
            GLCall(glDeleteShader(shader));
            return;
        }

        GLCall(glValidateProgram(m_program));

        int validateResult;
        GLCall(glGetProgramiv(m_program, GL_VALIDATE_STATUS, &validateResult));
        if (validateResult == GL_FALSE)
        {
            std::int32_t length;
            GLCall(glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length));

            std::string message;
            message.resize(length);

            GLCall(glGetProgramInfoLog(m_program, length, &length, &message[0]));
            sf::err() << "Failed to validate program!" << std::endl;
            sf::err() << message << std::endl;
            GLCall(glDeleteShader(shader));
            return;
        }

        GLCall(glDeleteShader(shader));
    }
    const Shader3D& Shader3D::getDefaultShader()
    {
        static Shader3D instance;
        static bool first = true;

        if (first)
        {
            static_cast<void>(instance.loadFromMemory(
#ifdef SFML_OPENGL_ES
                "#version 100\n"
                "attribute vec3 position;"
                "attribute vec4 color;"
                "varying vec4 sf_color;"
#else
                "#version 330 core\n"
                "in vec3 position;"
                "in vec4 color;"
                "out vec4 sf_color;"
#endif
                "uniform mat4 sf_model;"
                "uniform mat4 sf_view;"
                "uniform mat4 sf_proj;"
                "void main()"
                "{"
                "    sf_color = color;"
                "    gl_Position = sf_proj * sf_view * sf_model * vec4(position.xyz, 1.0);"
                "}", DDD::Shader3D::Vertex));
            static_cast<void>(instance.loadFromMemory(
#ifdef SFML_OPENGL_ES
                "#version 100\n"
                "precision mediump float;"
                "varying vec4 sf_color;"
#else
                "#version 330 core\n"
                "in vec4 sf_color;"
                "out vec4 out_color;"
#endif
                "void main()"
                "{"
#ifdef SFML_OPENGL_ES
                "    gl_FragColor = sf_color;"
#else
                "    out_color = sf_color;"
#endif
                "}", DDD::Shader3D::Fragment));
            first = false;
        }

        return instance;
    }

    const Shader3D& Shader3D::getDefaultTexShader()
    {
        static Shader3D instance;
        static bool first = true;

        if (first)
        {
            static_cast<void>(instance.loadFromMemory(
#ifdef SFML_OPENGL_ES
                "#version 100\n"
                "attribute vec3 position;"
                "attribute vec4 color;"
                "attribute vec2 texCoord;"
                "varying vec4 sf_color;"
                "varying vec2 sf_texCoord;"
#else
                "#version 330 core\n"
                "in vec3 position;"
                "in vec4 color;"
                "in vec2 texCoord;"
                "out vec4 sf_color;"
                "out vec2 sf_texCoord;"
#endif
                "uniform mat4 sf_model;"
                "uniform mat4 sf_view;"
                "uniform mat4 sf_proj;"
                "void main()"
                "{"
                "    sf_color = color;"
                "    sf_texCoord = texCoord;"
                "    gl_Position = sf_proj * sf_view * sf_model * vec4(position.xyz, 1.0);"
                "}", DDD::Shader3D::Vertex));
            static_cast<void>(instance.loadFromMemory(

#ifdef SFML_OPENGL_ES
                "#version 100\n"
                "precision mediump float;"
                "varying vec4 sf_color;"
                "varying vec2 sf_texCoord;"
#else
                "#version 330 core\n"
                "in vec4 sf_color;"
                "in vec2 sf_texCoord;"
                "out vec4 out_color;"
#endif
                "uniform sampler2D sf_samplers[1];"
                "uniform mat4 sf_texture;"
                "uniform vec2 factor_npot;"
                "void main()"
                "{"
                "    vec4 coord = sf_texture * vec4(sf_texCoord, 0.0, 1.0);"
                "    coord.xy = mod(coord.xy, factor_npot.xy);"
                "    vec4 col = texture2D(sf_samplers[0], coord.xy) * sf_color;"
#ifdef SFML_OPENGL_ES
                "    gl_FragColor = col;"
#else
                "    out_color = col;"
#endif
                "}", DDD::Shader3D::Fragment));
            first = false;
        }

        return instance;
    }
    void Shader3D::setSamplers(std::uint32_t count) const
    {
        std::int32_t loc = GetUniformLocation("sf_samplers");
        std::int32_t* samplers = new std::int32_t[count];
        for (std::int32_t i = 0; i < count; i++)
            samplers[i] = i;
        GLCall(glUniform1iv(loc, count, samplers));
        delete[] samplers;
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