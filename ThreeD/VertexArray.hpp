#pragma once
#include <cstdint>
#include <vector>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace DDD
{
	template<typename T>
	class VertexArray3D
	{
		std::uint32_t m_array;
		const IndexBuffer3D* indexBuffer = nullptr;
		const VertexBuffer3D<T>* vertexBuffer = nullptr;
	public:
		VertexArray3D();
		VertexArray3D(const VertexBuffer3D<T>* vertexBuffer, const IndexBuffer3D* indexBuffer);
		~VertexArray3D();
		std::uint32_t getHandle() const;
		const VertexBuffer3D<T>* getVertexBuffer() const;
		const IndexBuffer3D* getIndexBuffer() const;

		void setBuffers(const VertexBuffer3D<T>* vertexBuffer, const IndexBuffer3D* indexBuffer);
		void UpdateVertexBuffer() const;
		void UpdateIndexBuffer() const;
	};
	template <typename T>
    void BindVertexArray(const VertexArray3D<T>* vao);
}

#include "VertexArray.inl"