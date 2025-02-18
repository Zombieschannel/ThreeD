#include "RenderTarget.hpp"

namespace DDD
{
    template<typename T>
    void RenderTarget3D::draw3D(const VertexArray3D<T>* vao, sf::PrimitiveType type, const RenderStates3D& states)
    {
        if (!vao)
            return;
        GLCall(glBlendFunc(states.blendMode.colorSrcFactor, states.blendMode.colorDstFactor));
        GLCall(glBlendEquation(states.blendMode.colorEquation));
        
        BindVertexArray(vao);
        if (states.shader)
            BindShader(states.shader);
        if (states.shader)
        {
            states.shader->setUniform("u_model", states.transform);
            states.shader->setUniform("u_view", getView3D().getTransform());
            states.shader->setUniform("u_proj", getProjection3D().getTransform());
        }
        if (states.texture)
            BindTexture(states.texture);
        else
            BindTexture(nullptr);
        if (states.shader && states.texture)
            states.shader->setUniform("u_textures[0]", *states.texture);

        if (vao->getIndexBuffer())
        {
            GLCall(glDrawElements(type, vao->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_SHORT, nullptr));
        }
        else
        {
            GLCall(glDrawArrays(type, 0, vao->getVertexBuffer()->getVertexCount()));
        }

    }
}