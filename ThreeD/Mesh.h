#pragma once
#include "Model.h"
#include "Transformable.h"
#include "RenderTarget.h"
#include "PrimitiveType.h"
#include "Drawable.h"
#include "Maths.h"
#include <vector>
namespace DDD
{
	class RenderTarget3D;
	class Mesh3D : public Drawable3D, public Transformable3D
	{
		Model3D* model = nullptr;
		const Material3D* material = nullptr;
	public:
		void setModel(Model3D& model)
		{
			this->model = &model;
		}
		void setMaterial(const Material3D& material)
		{
			this->material = &material;
		}
		Model3D& getModel() const
		{
			return *model;
		}
		const Material3D& getMaterial() const
		{
			return *material;
		}
		VertexArray3D& getVAO()
		{
			return model->vao;
		}
		CustomVertexBuffer3D& getVBO()
		{
			return model->vbo;
		}
		//void recalculateNormals()
		//{
		//	for (int i = 0; i < model->getVertexBuffer().getVertexCount() / 3; i++)
		//	{
		//		sf::Vector3f normal;
		//		sf::Vector3f pos1 = getTransform().transformPoint(model->vbo[i * 3].getPosition());
		//		sf::Vector3f pos2 = getTransform().transformPoint(model->vbo[i * 3 + 1].getPosition());
		//		sf::Vector3f pos3 = getTransform().transformPoint(model->vbo[i * 3 + 2].getPosition());
		//		normal = calculateNormal(pos1, pos2, pos3);
		//		//sf::err() << normal.x << std::endl;
		//		//sf::err() << normal.y << std::endl;
		//		//sf::err() << normal.z << std::endl;
		//		model->vbo[i * 3].setNormal(normal);
		//		model->vbo[i * 3 + 1].setNormal(normal);
		//		model->vbo[i * 3 + 2].setNormal(normal);
		//	}
		//	model->vao.setVBO(model->vbo);
		//}
	private:
		virtual void draw(RenderTarget3D& target, RenderStates3D states) const
		{
			states.transform *= getTransform();
			if (material)
				states.material = material;
			target.draw3D(&model->vao, DDD::PrimitiveType3D::Triangles, states);
		}
		/*void draw()
		{
			for (auto& n : model->vbo)
			{
				VertexBuffer3D::Bind(n.second);
				GLCall(glDrawElements(GL_TRIANGLES, n.second.getIndexBuffer().getIndexCount(), GL_UNSIGNED_INT, nullptr));
			}
		}*/
	};
}