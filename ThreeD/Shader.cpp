#include "Shader.hpp"

namespace DDD
{
    std::int32_t Shader3D::GetUniformLocation(const std::string& name) const
    {
        if (uniformLocationCache.contains(name))
            return uniformLocationCache[name];

        GLCall(const std::int32_t location = glGetUniformLocation(m_program, name.c_str()));

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
    bool Shader3D::loadFromFile(const std::filesystem::path& path, const Type type)
    {
        sf::FileInputStream stream;
        if (!stream.open(path))
        {
            sf::err() << "Could not open shader!" << std::endl;
            return false;
        }
        loadFromStream(stream, type);
        return true;
    }
    void Shader3D::loadFromMemory(const void* data, const std::uint32_t size, const Type type)
    {
        sf::MemoryInputStream stream(data, size);
        loadFromStream(stream, type);
    }
    void Shader3D::loadFromStream(sf::InputStream& stream, const Type type)
    {
        std::string tmp;
        tmp.resize(*stream.getSize());
        if (!stream.read(&tmp[0], *stream.getSize()))
            return;

        if (!m_program)
        {
            GLCall(m_program = glCreateProgram());
        }

        std::int32_t shaderType = 0;
        switch (type)
        {
        case Vertex: shaderType = GL_VERTEX_SHADER; break;
        case Fragment: shaderType = GL_FRAGMENT_SHADER; break;
        case Geometry: shaderType = GL_GEOMETRY_SHADER; break;
        }

        GLCall(std::uint32_t shader = glCreateShader(shaderType));

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
            const std::string v =
#ifdef SFML_OPENGL_ES
            "#version 300 es\n"
#else
            "#version 330 core\n"
#endif
            "in vec3 position;"
            "in vec4 color;"
            "out vec4 out_color;"
            "uniform mat4 DDD_model;"
            "uniform mat4 DDD_view;"
            "uniform mat4 DDD_proj;"
            "void main()"
            "{"
            "    out_color = color;"
            "    gl_Position = DDD_proj * DDD_view * DDD_model * vec4(position.xyz, 1.0);"
            "}";
            const std::string f =
#ifdef SFML_OPENGL_ES
            "#version 300 es\n"
            "precision mediump float;"
#else
            "#version 330 core\n"
#endif
            "in vec4 out_color;"
            "out vec4 DDD_color;"
            "void main()"
            "{"
            "    DDD_color = out_color;"
            "}";
            instance.loadFromMemory(v.c_str(), v.length(), Vertex);
            instance.loadFromMemory(f.c_str(), f.length(), Fragment);
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
            const std::string v =
#ifdef SFML_OPENGL_ES
            "#version 300 es\n"
#else
            "#version 330 core\n"
#endif
            "in vec3 position;"
            "in vec4 color;"
            "in vec2 texCoord;"
            "out vec4 out_color;"
            "out vec2 out_texCoord;"
            "uniform mat4 DDD_model;"
            "uniform mat4 DDD_view;"
            "uniform mat4 DDD_proj;"
            "void main()"
            "{"
            "    out_color = color;"
            "    out_texCoord = texCoord;"
            "    gl_Position = DDD_proj * DDD_view * DDD_model * vec4(position.xyz, 1.0);"
            "}";
            const std::string f =
#ifdef SFML_OPENGL_ES
            "#version 300 es\n"
            "precision mediump float;"
#else
            "#version 330 core\n"
#endif
            "in vec4 out_color;"
            "in vec2 out_texCoord;"
            "out vec4 DDD_color;"
            "uniform sampler2D DDD_samplers[1];"
            "uniform mat4 DDD_texture;"
            "void main()"
            "{"
            "    vec4 coord = DDD_texture * vec4(out_texCoord, 0.0, 1.0);"
            "    vec4 col = texture2D(DDD_samplers[0], coord.xy) * out_color;"
            "    DDD_color = col;"
            "}";
            instance.loadFromMemory(v.c_str(), v.length(), Vertex);
            instance.loadFromMemory(f.c_str(), f.length(), Fragment);
            first = false;
        }

        return instance;
    }
    void Shader3D::setSamplers(const std::uint32_t count) const
    {
        const std::int32_t loc = GetUniformLocation("DDD_samplers");
        std::vector<std::int32_t> samplers;
        samplers.resize(count);
        for (std::int32_t i = 0; i < count; i++)
            samplers.at(i) = i;
        GLCall(glUniform1iv(loc, count, &samplers[0]));
    }
    void Shader3D::setUniform(const std::string& name, const Transform3D& v) const
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, v.getMatrix()));
    }
    void Shader3D::setUniformMat3(const std::string& name, const float *first) const
    {
        GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, first));
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