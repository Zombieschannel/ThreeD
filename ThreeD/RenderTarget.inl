#include "RenderTarget.hpp"
#include "Shader.hpp"

namespace DDD
{
    template<typename T>
    void RenderTarget3D::draw(const VertexArray3D<T>* vao, sf::PrimitiveType type, const RenderStates3D& states)
    {
        if (!vao)
            return;
        draw(vao->getVertexBuffer(), vao->getIndexBuffer(), type, states);
    }
    template<typename T>
    void RenderTarget3D::draw(const VertexBuffer3D<T>* vbo, const IndexBuffer3D* ibo, sf::PrimitiveType type, const RenderStates3D& states)
    {
        if (!vbo)
            return;
        GLCall(glViewport(m_proj3D.getViewport().position.x, m_proj3D.getViewport().position.y, m_proj3D.getViewport().size.x, m_proj3D.getViewport().size.y));
        
        GLCall(glBlendFunc(blendFactorToGLtype(states.blendMode.colorSrcFactor), blendFactorToGLtype(states.blendMode.colorDstFactor)));
        GLCall(glBlendEquation(blendEquationToGLtype(states.blendMode.colorEquation)));

        BindVertexBuffer(vbo);
        BindIndexBuffer(ibo);

        std::vector<std::uint8_t> attribLoc;
        const Shader3D* shader = states.shader;
        if (shader)
        {
            BindShader(states.shader);
            attribLoc = vbo->getAttribLocation();
        }
        else
        {
            if (states.texture)
            {
                BindShader(&Shader3D::getDefaultTexShader());
                if (m_shaderCache.texPos < 0)
                {
                    GLCall(m_shaderCache.texPos = glGetAttribLocation(Shader3D::getDefaultTexShader().getHandle(), "position"));
                    GLCall(m_shaderCache.texCol = glGetAttribLocation(Shader3D::getDefaultTexShader().getHandle(), "color"));
                    GLCall(m_shaderCache.texTex = glGetAttribLocation(Shader3D::getDefaultTexShader().getHandle(), "texCoord"));
                }
                attribLoc = { m_shaderCache.texPos, m_shaderCache.texCol, m_shaderCache.texTex };
                shader = &Shader3D::getDefaultTexShader();
            }
            else
            {
                BindShader(&Shader3D::getDefaultShader());
                if (m_shaderCache.defPos < 0)
                {
                    GLCall(m_shaderCache.defPos = glGetAttribLocation(Shader3D::getDefaultShader().getHandle(), "position"));
                    GLCall(m_shaderCache.defCol = glGetAttribLocation(Shader3D::getDefaultShader().getHandle(), "color"));
                }
                attribLoc = { m_shaderCache.defPos, m_shaderCache.defCol };
                shader = &Shader3D::getDefaultShader();
            }
        }
        shader->setUniform("sf_model", states.transform);
        shader->setUniform("sf_view", getView3D().getTransform());
        shader->setUniform("sf_proj", getProjection3D().getTransform());

        TextureSlot(0);
        if (states.texture)
            BindTexture(states.texture);
        else
            BindTexture(nullptr);
        if (states.texture)
            shader->setUniform("u_textures[0]", 0);
        
        std::uint32_t offset = 0;
        for (std::uint32_t i = 0; T::componentCount(i) > 0 && i < attribLoc.size(); i++)
        {
            GLCall(glEnableVertexAttribArray(attribLoc[i]));
            GLCall(glVertexAttribPointer(attribLoc[i], T::componentCount(i), componentToGLtype(T::componentType(i)),
                GL_FALSE, sizeof(T), reinterpret_cast<const void*>(offset)));
            offset += T::componentCount(i) * componentToGLsize(T::componentType(i));
        }

        if (ibo)
        {
            GLCall(glDrawElements(primitiveTypeToGLtype(type), ibo->getIndexCount(), GL_UNSIGNED_SHORT, nullptr));
        }
        else
        {
            GLCall(glDrawArrays(primitiveTypeToGLtype(type), 0, vbo->getVertexCount()));
        }

        for (std::uint32_t i = 0; T::componentCount(i) > 0 && i < attribLoc.size(); i++)
        {
            GLCall(glDisableVertexAttribArray(attribLoc[i]));
        }

    }
}