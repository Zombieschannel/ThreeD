#include "RenderTarget.hpp"

namespace DDD
{
    template<typename T>
    void RenderTarget3D::draw(const VertexArray3D<T>* vao, sf::PrimitiveType type, const RenderStates3D& states)
    {
        if (!vao)
            return;
        draw3D(vao->getVertexBuffer(), vao->getIndexBuffer());
    }
    template<typename T>
    void RenderTarget3D::draw(const VertexBuffer3D<T>* vbo, const IndexBuffer3D* ibo, sf::PrimitiveType type, const RenderStates3D& states)
    {
        if (!vbo)
            return;
        GLCall(glViewport(proj.getViewport().left, proj.getViewport().top, proj.getViewport().width, proj.getViewport().height));
        
        GLCall(glBlendFunc(blendFactorToGLtype(states.blendMode.colorSrcFactor), blendFactorToGLtype(states.blendMode.colorDstFactor)));
        GLCall(glBlendEquation(blendEquationToGLtype(states.blendMode.colorEquation)));

        BindVertexBuffer(vbo);
        BindIndexBuffer(ibo);
        if (states.shader)
            BindShader(states.shader);
        if (states.shader)
        {
            states.shader->setUniform("u_model", states.transform);
            states.shader->setUniform("u_view", getView().getTransform());
            states.shader->setUniform("u_proj", getProjection().getTransform());
        }

        TextureSlot(0);
        if (states.texture)
            BindTexture(states.texture);
        else
            BindTexture(nullptr);
        if (states.shader && states.texture)
            states.shader->setUniform("u_textures[0]", 0);
        
        std::uint32_t offset = 0;
        for (std::uint32_t i = 0; T::componentCount(i) > 0 && i < vbo->getAttribLocation().size(); i++)
        {
            GLCall(glEnableVertexAttribArray(vbo->getAttribLocation()[i]));
            GLCall(glVertexAttribPointer(vbo->getAttribLocation()[i], T::componentCount(i), componentToGLtype(T::componentType(i)),
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

    }
}