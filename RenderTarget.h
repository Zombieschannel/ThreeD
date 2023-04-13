#pragma once
#include "Drawable.h"
#include "View.h"
#include "Projection.h"
#include "VertexArray.h"
#include "PrimitiveType.h"
#include "Material.h"
namespace DDD
{

    class RenderTarget3D
    {
    public:
        virtual ~RenderTarget3D()
        {

        }

        void clear3D(const sf::Color& color = sf::Color(0, 0, 0, 255), unsigned int clearCall = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        {
            GLCall(glClearColor(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0));
            GLCall(glClear(clearCall));
        }

        void setView3D(const View3D& view)
        {
            this->view = view;
        }

        const View3D& getView3D() const
        {
            return view;
        }
        void setProjection3D(const Projection3D& proj)
        {
            this->proj = proj;
        }

        const Projection3D& getProjection3D() const
        {
            return proj;
        }

       /* IntRect getViewport(const View3D& view) const
        {
            view.getViewPort();
        }*/

       
        void draw3D(const Drawable3D& drawable, const RenderStates3D& states = RenderStates3D::Default)
        {
            drawable.draw(*this, states);
        }
       
        void draw3D(const VertexArray3D* vao,
            PrimitiveType3D type = PrimitiveType3D::Points, const RenderStates3D& states = RenderStates3D::Default)
        {
            if (!vao)
                return;
            GLCall(glBlendFunc(states.blendMode.colorSrcFactor, states.blendMode.colorDstFactor));
            GLCall(glBlendEquation(states.blendMode.colorEquation));
            
            VertexArray3D::Bind(*vao);
            if (states.shader)
                Shader3D::Bind(states.shader);
            if (states.shader)
            {
                states.shader->setUniform("u_model", states.transform);
                states.shader->setUniform("u_view", getView3D().getTransform());
                states.shader->setUniform("u_proj", getProjection3D().getTransform());
            }
            if (states.shader && states.material)
            {
                states.shader->setUniform("m_ambient", states.material->getAmbient());
                states.shader->setUniform("m_diffuse", states.material->getDiffuse());
                states.shader->setUniform("m_specular", states.material->getSpecular());
                states.shader->setUniform("m_emission", states.material->getEmission());
                states.shader->setUniform("m_highlights", states.material->getHighlights());
            }
            if (states.texture)
                Texture3D::Bind(states.texture);
            else
                Texture3D::Bind(nullptr);
            if (states.shader && states.texture)
                states.shader->setUniform("u_textures[0]", *states.texture);

            if (&vao->getIndexBuffer() != nullptr)
            {
                GLCall(glDrawElements(type, vao->getIndexBuffer().getIndexCount(), GL_UNSIGNED_INT, nullptr));
            }
            else
            {
                GLCall(glDrawArrays(type, 0, vao->getVertexBuffer().getVertexCount()));
            }

        }

        //virtual Vector2u getSize() const = 0;

        //virtual bool setActive(bool active = true);

    protected:

        RenderTarget3D()
        {

        }
    private:
        View3D view; 
        Projection3D proj;
   };
}