#pragma once
#include <cstdint>
#include <vector>
#include "OpenGL.hpp"
#include "DrawType.hpp"

namespace DDD
{
	class IndexBuffer3D
	{
    private:
		std::vector<std::uint16_t> indices;
        DrawType drawType = DrawType::Dynamic;
        std::uint32_t ID = 0;
    public:
        IndexBuffer3D();
        IndexBuffer3D(std::uint32_t vertexCount);
        ~IndexBuffer3D();

        std::uint32_t getHandle() const;
        std::uint32_t getIndexCount() const;
        DrawType getDrawType() const;

        std::uint16_t& operator [](std::uint32_t index);
        const std::uint16_t& operator [](std::uint32_t index) const;

        void clear();
        void resize(std::uint32_t indexCount);
        void append(std::uint16_t index);
        void setDrawType(DrawType type);
        void Update();
	};
    static void BindIndexBuffer(const IndexBuffer3D* buffer);
}